// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GEGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "GEGameplayTags.h"

UGEGameplayAbility::UGEGameplayAbility()
{
    /* 기본 설정 */

    // 인스턴싱 정책
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    // 실행 정책
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;

    // 입력 리플리케이트
    bReplicateInputDirectly = true;

    /* 태그 설정 */

    using namespace GEGameplayTags;

    // 기본 어빌리티 태그 설정
    AbilityTags.AddTagFast(Action::Root);
    ActivationOwnedTags.AddTagFast(Action::Root);

    // ActivationBlockedTags 설정
    ActivationBlockedTags.AddTagFast(State::Dead);
    ActivationBlockedTags.AddTagFast(State::Knockdown);
    ActivationBlockedTags.AddTagFast(State::Stun);
}

bool UGEGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
    const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
    if(InstancingPolicy == EGameplayAbilityInstancingPolicy::InstancedPerActor)
    {
        auto AbilitySpec = ActorInfo->AbilitySystemComponent->FindAbilitySpecFromHandle(Handle);
        auto AbilityInstance = CastChecked<UGEGameplayAbility>(AbilitySpec->GetPrimaryInstance());

        return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) && AbilityInstance->CanActivate();
    }

    return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UGEGameplayAbility::InputPressed(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    Super::InputPressed(Handle, ActorInfo, ActivationInfo);

    // 어빌리티 입력이 활성화되었지만 어빌리티가 활성화되지 않은 경우 실패한 것으로 간주하여 어빌리티 입력을 초기화합니다.
    GetCurrentAbilitySpec()->InputPressed = GetCurrentAbilitySpec()->IsActive();
}

void UGEGameplayAbility::InputReleased(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    Super::InputReleased(Handle, ActorInfo, ActivationInfo);

    // 어빌리티 입력이 비활성화되면 어빌리티를 종료합니다.
    if(GetCurrentAbilitySpec()->IsActive()) EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGEGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    // 어빌리티가 종료되는 경우 어빌리티 입력을 초기화합니다.
    GetCurrentAbilitySpec()->InputPressed = false;
}
