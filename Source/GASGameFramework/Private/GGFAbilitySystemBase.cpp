// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFAbilitySystemBase.h"

#include "GGFGameplayTags.h"
#include "Abilities/GGFGameplayAbility.h"
#include "Attributes/GGFStaminaAttributes.h"
#include "Effects/GE_GGFDefaultAttributes.h"
#include "FunctionLibraries/GGFFunctionLibrary.h"

UGGFAbilitySystemBase::UGGFAbilitySystemBase()
{
    // 설정
    bWantsInitializeComponent = true;

    // 기본 Attributes 및 GameplayEffect 등록
    DefaultAttributes.Add(UGGFStaminaAttributes::StaticClass());
    DefaultEffects.Add(UGE_GGFDefaultAttributes::StaticClass());
}

void UGGFAbilitySystemBase::InitializeComponent()
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

void UGGFAbilitySystemBase::PressInputTag(FGameplayTag InputTag)
{
    // 디버깅을 위한 입력 태그를 추가합니다.
    if(!HasMatchingGameplayTag(InputTag)) AddLooseGameplayTag(InputTag);

    PressInputID(GetTypeHash(InputTag));
}

void UGGFAbilitySystemBase::ReleaseInputTag(FGameplayTag InputTag)
{
    // 디버깅을 위한 입력 태그를 제거합니다.
    if(HasMatchingGameplayTag(InputTag)) RemoveLooseGameplayTag(InputTag);

    ReleaseInputID(GetTypeHash(InputTag));
}

void UGGFAbilitySystemBase::AbilityLocalInputPressed(int32 InputID)
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

void UGGFAbilitySystemBase::AbilityLocalInputReleased(int32 InputID)
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

void UGGFAbilitySystemBase::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
    Super::OnGiveAbility(AbilitySpec);

    // InputTag의 해시 값을 사용하여 InputID 설정
    if(AbilitySpec.Ability && AbilitySpec.Ability->GetClass()->ImplementsInterface(UGGFAbilityInputTagInterface::StaticClass()))
    {
        const FGameplayTag& InputTag = IGGFAbilityInputTagInterface::Execute_GetInputTag(AbilitySpec.Ability);
        AbilitySpec.InputID = GetTypeHash(InputTag);
    }
}

void UGGFAbilitySystemBase::OnDead_Implementation()
{
    AddLooseGameplayTag(GGFGameplayTags::State::Dead);
}

void UGGFAbilitySystemBase::InitializeAbilitySystem()
{
    // 기본 AttributeSet 생성 및 등록
    UGGFFunctionLibrary::AddAttributeSetsToSystem(DefaultAttributes, this);

    // 기본 GameplayEffect 적용
    UGGFFunctionLibrary::ApplyGameplayEffectsToSystem(DefaultEffects, this);

    // 기본 GameplayAbility 부여
    UGGFFunctionLibrary::GiveAbilitiesToSystem(DefaultAbilities, this);
}

void UGGFAbilitySystemBase::BindHealthAttributeDelegate()
{
    FOnGameplayAttributeValueChange& Delegate = GetGameplayAttributeValueChangeDelegate(UGGFHealthAttributes::GetHealthAttribute());
    Delegate.AddLambda([this](const FOnAttributeChangeData& OnAttributeChangeData)
    {
        if(FMath::IsNearlyZero(OnAttributeChangeData.NewValue))
            OnDead();
    });
}
