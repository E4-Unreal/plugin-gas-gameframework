// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFPA_Interact.h"

#include "AbilitySystemComponent.h"
#include "GGFInteractionGameplayTags.h"
#include "Abilities/GGFAT_DetectInteractableActor.h"
#include "Interfaces/GGFInteractableInterface.h"

UGGFPA_Interact::UGGFPA_Interact()
{
    // 입력 태그 설정
    InputTag = GGFGameplayTags::Input::Interact;

    // 상호작용 가능 상태 태그 트리거 설정
    FAbilityTriggerData TriggerData;
    TriggerData.TriggerTag = GGFGameplayTags::State::Interactable;
    TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagPresent;

    AbilityTriggers.Emplace(TriggerData);
}

bool UGGFPA_Interact::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
    const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
    UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponentFromActorInfo();
    return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) && AbilitySystem && AbilitySystem->HasMatchingGameplayTag(GGFGameplayTags::State::Interactable);
}

void UGGFPA_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // 상호작용 가능한 오브젝트 감지를 위한 어빌리티 태스크 생성
    bool ShowDebug = false;
#if WITH_EDITOR
    ShowDebug = bShowDebug;
#endif

    auto DetectInteractableActorTask = UGGFAT_DetectInteractableActor::CreateTask(this, ShowDebug, MaxDistance, SphereRadius);
    DetectInteractableActorTask->OnInteractableActorDetected.AddDynamic(this, &ThisClass::UGGFPA_Interact::OnInteractableActorDetected_Event);
    DetectInteractableActorTask->ReadyForActivation();
}

void UGGFPA_Interact::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    // 기존 오브젝트 비활성화
    if(InteractableActor.IsValid())
    {
        IGGFInteractableInterface::Execute_Deactivate(InteractableActor.Get(), GetAvatarActorFromActorInfo());
        InteractableActor = nullptr;
    }
}

void UGGFPA_Interact::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo)
{
    Super::InputPressed(Handle, ActorInfo, ActivationInfo);

    // 상호작용 시작
    if(InteractableActor.IsValid())
    {
        IGGFInteractableInterface::Execute_StartInteraction(InteractableActor.Get(), GetAvatarActorFromActorInfo());
    }
}

void UGGFPA_Interact::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo)
{
    // 상호작용 종료
    if(bIsActive && InteractableActor.IsValid())
    {
        IGGFInteractableInterface::Execute_StopInteraction(InteractableActor.Get(), GetAvatarActorFromActorInfo());
    }
}

void UGGFPA_Interact::ActivateInteractableObject(bool bActive)
{
    // 유효성 검사
    if(!InteractableActor.IsValid()) return;

    // 로컬 플레이어인 경우
    APawn* AvatarPawn = Cast<APawn>(GetAvatarActorFromActorInfo());
    if(AvatarPawn && AvatarPawn->Controller && AvatarPawn->Controller->IsLocalPlayerController())
    {
        if(bActive) IGGFInteractableInterface::Execute_Activate(InteractableActor.Get(), GetAvatarActorFromActorInfo());
        else IGGFInteractableInterface::Execute_Deactivate(InteractableActor.Get(), GetAvatarActorFromActorInfo());
    }
    else
    {
        IGGFInteractableInterface::Execute_Deactivate(InteractableActor.Get(), GetAvatarActorFromActorInfo());
    }
}

void UGGFPA_Interact::OnInteractableActorDetected_Event(AActor* NewInteractableActor)
{
    // 이미 감지된 오브젝트와 동일한 경우 무시
    if(InteractableActor == NewInteractableActor) return;

    // 기존 오브젝트 비활성화
    ActivateInteractableObject(false);

    // 새로운 오브젝트 할당
    InteractableActor = NewInteractableActor;

    // 새로운 오브젝트 활성화
    ActivateInteractableObject(true);
}
