// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GGFStateAbility.h"

#include "GGFGameplayTags.h"
#include "GameFramework/Character.h"

UGGFStateAbility::UGGFStateAbility()
{
    // 기본 인스턴싱 정책 설정
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    /* 태그 설정 */
    // ActivationBlockedTags 설정
    ActivationBlockedTags.AddTagFast(GGFGameplayTags::State::Dead);
}

void UGGFStateAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // State Enter
    OnEnter();
}

void UGGFStateAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    // State Exit
    OnExit();
}

void UGGFStateAbility::OnEnter_Implementation()
{
}

void UGGFStateAbility::OnExit_Implementation()
{
}
