// Fill out your copyright notice in the Description page of Project Settings.

#include "GEAbilitySystem.h"

#include "GEGameplayTags.h"
#include "Abilities/GEGameplayAbility.h"
#include "GEBlueprintFunctionLibrary.h"
#include "Attributes/GEHealthAttributes.h"

UGEAbilitySystem::UGEAbilitySystem()
{
    // 설정
    bWantsInitializeComponent = true;
}

void UGEAbilitySystem::InitializeComponent()
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

void UGEAbilitySystem::PressInputTag(FGameplayTag InputTag)
{
    // 디버깅을 위한 입력 태그를 추가합니다.
    if(!HasMatchingGameplayTag(InputTag)) AddLooseGameplayTag(InputTag);

    PressInputID(GetTypeHash(InputTag));
}

void UGEAbilitySystem::ReleaseInputTag(FGameplayTag InputTag)
{
    // 디버깅을 위한 입력 태그를 제거합니다.
    if(HasMatchingGameplayTag(InputTag)) RemoveLooseGameplayTag(InputTag);

    ReleaseInputID(GetTypeHash(InputTag));
}

void UGEAbilitySystem::AbilityLocalInputPressed(int32 InputID)
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

void UGEAbilitySystem::AbilityLocalInputReleased(int32 InputID)
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

void UGEAbilitySystem::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
    Super::OnGiveAbility(AbilitySpec);

    // InputTag의 해시 값을 사용하여 InputID 설정
    if(UGEGameplayAbility* Ability = Cast<UGEGameplayAbility>(AbilitySpec.Ability))
    {
        const FGameplayTag& InputTag = Ability->GetInputTag();
        AbilitySpec.InputID = GetTypeHash(InputTag);
    }
}

void UGEAbilitySystem::OnDead_Implementation()
{
    AddLooseGameplayTag(GEGameplayTags::State::Dead);
}

void UGEAbilitySystem::InitializeAbilitySystem()
{
    // 기본 AttributeSet 생성 및 등록
    UGEBlueprintFunctionLibrary::AddAttributeSetsToSystem(DefaultAttributes, this);

    // 기본 GameplayEffect 적용
    UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToSystem(DefaultEffects, this);

    // 기본 GameplayAbility 부여
    UGEBlueprintFunctionLibrary::GiveAbilitiesToSystem(DefaultAbilities, this);
}

void UGEAbilitySystem::BindHealthAttributeDelegate()
{
    FOnGameplayAttributeValueChange& Delegate = GetGameplayAttributeValueChangeDelegate(UGEHealthAttributes::GetHealthAttribute());
    Delegate.AddLambda([this](const FOnAttributeChangeData& OnAttributeChangeData)
    {
        if(FMath::IsNearlyZero(OnAttributeChangeData.NewValue))
            OnDead();
    });
}
