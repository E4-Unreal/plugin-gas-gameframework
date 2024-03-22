// Fill out your copyright notice in the Description page of Project Settings.

#include "GEAbilitySystemBase.h"

#include "GEGameplayTags.h"
#include "Abilities/GEGameplayAbilityBase.h"
#include "Attributes/GEStaminaAttributes.h"
#include "Effects/GE_GEDefaultAttributes.h"
#include "FunctionLibraries/GEFunctionLibrary.h"

UGEAbilitySystemBase::UGEAbilitySystemBase()
{
    // 설정
    bWantsInitializeComponent = true;

    // 기본 Attributes 및 GameplayEffect 등록
    DefaultAttributes.Add(UGEStaminaAttributes::StaticClass());
    DefaultEffects.Add(UGE_GEDefaultAttributes::StaticClass());
}

void UGEAbilitySystemBase::InitializeComponent()
{
    Super::InitializeComponent();

    // 서버에서만 초기화 진행
    if(IsOwnerActorAuthoritative())
    {
        // AttributeSet 설정 및 초기화
        InitializeAbilitySystem();
    }

    // OnDead 이벤트를 체력 어트리뷰트 델리게이트에 바인딩
    BindHealthAttributeDelegate();
}

void UGEAbilitySystemBase::PressInputTag(const FGameplayTag& InputTag)
{
    // 디버깅을 위한 입력 태그를 추가합니다.
    if(!HasMatchingGameplayTag(InputTag)) AddLooseGameplayTag(InputTag);

    PressInputID(GetTypeHash(InputTag));
}

void UGEAbilitySystemBase::ReleaseInputTag(const FGameplayTag& InputTag)
{
    // 디버깅을 위한 입력 태그를 제거합니다.
    if(HasMatchingGameplayTag(InputTag)) RemoveLooseGameplayTag(InputTag);

    ReleaseInputID(GetTypeHash(InputTag));
}

void UGEAbilitySystemBase::AbilityLocalInputPressed(int32 InputID)
{
    // Consume the input if this InputID is overloaded with GenericConfirm/Cancel and the GenericConfim/Cancel callback is bound
    if (IsGenericConfirmInputBound(InputID))
    {
        LocalInputConfirm();
        return;
    }

    if (IsGenericCancelInputBound(InputID))
    {
        LocalInputCancel();
        return;
    }

    // ---------------------------------------------------------

    ABILITYLIST_SCOPE_LOCK();

    // 마지막으로 추가된 Ability만 Press합니다.
    for (int i = ActivatableAbilities.Items.Num() - 1; i >= 0; i--)
    {
        FGameplayAbilitySpec& Spec = ActivatableAbilities.Items[i];

        // Input ID 검사
        if(Spec.InputID != InputID) continue;

        // Ability 유효성 검사
        if(Spec.Ability == nullptr) continue;

        // Ability Press
        Spec.InputPressed = true;

        if (Spec.IsActive())
        {
            if (Spec.Ability->bReplicateInputDirectly && IsOwnerActorAuthoritative() == false)
            {
                ServerSetInputPressed(Spec.Handle);
            }

            AbilitySpecInputPressed(Spec);

            // Invoke the InputPressed event. This is not replicated here. If someone is listening, they may replicate the InputPressed event to the server.
            InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
        }
        else
        {
            // Ability is not active, so try to activate it
            TryActivateAbility(Spec.Handle);
        }

        // 한 번의 입력으로 하나의 Ability만 발동이 가능합니다.
        break;
    }
}

void UGEAbilitySystemBase::AbilityLocalInputReleased(int32 InputID)
{
    ABILITYLIST_SCOPE_LOCK();

    // 마지막으로 추가된 Ability만 Release합니다.
    for (int i = ActivatableAbilities.Items.Num() - 1; i >= 0; i--)
    {
        FGameplayAbilitySpec& Spec = ActivatableAbilities.Items[i];

        // Input ID 검사
        if(Spec.InputID != InputID) continue;

        // Ability 유효성 검사
        if(Spec.Ability == nullptr || !Spec.IsActive()) continue;

        // Ability Release
        Spec.InputPressed = false;

        if (Spec.Ability->bReplicateInputDirectly && IsOwnerActorAuthoritative() == false)
        {
            ServerSetInputReleased(Spec.Handle);
        }

        AbilitySpecInputReleased(Spec);

        InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
    }
}

void UGEAbilitySystemBase::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
    Super::OnGiveAbility(AbilitySpec);

    // InputTag의 해시 값을 사용하여 InputID 설정
    if(AbilitySpec.Ability->GetClass()->ImplementsInterface(UGEAbilityInputTagInterface::StaticClass()))
    {
        const FGameplayTag& InputTag = IGEAbilityInputTagInterface::Execute_GetInputTag(AbilitySpec.Ability);
        AbilitySpec.InputID = GetTypeHash(InputTag);
    }
}

void UGEAbilitySystemBase::OnDead_Implementation()
{
    AddLooseGameplayTag(GEGameplayTags::State::Dead);
}

void UGEAbilitySystemBase::InitializeAbilitySystem()
{
    // 기본 AttributeSet 생성 및 등록
    UGEFunctionLibrary::AddAttributeSetsToSystem(DefaultAttributes, this);

    // 기본 GameplayEffect 적용
    UGEFunctionLibrary::ApplyGameplayEffectsToSystem(DefaultEffects, this);

    // 기본 GameplayAbility 부여
    UGEFunctionLibrary::GiveAbilitiesToSystem(DefaultAbilities, this);
}

void UGEAbilitySystemBase::BindHealthAttributeDelegate()
{
    FOnGameplayAttributeValueChange& Delegate = GetGameplayAttributeValueChangeDelegate(UGEHealthAttributes::GetHealthAttribute());
    Delegate.AddLambda([this](const FOnAttributeChangeData& OnAttributeChangeData)
    {
        if(FMath::IsNearlyZero(OnAttributeChangeData.NewValue))
            OnDead();
    });
}
