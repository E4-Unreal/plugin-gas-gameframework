// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GEGameplayAbility.h"

#include "GEGameplayTags.h"

UGEGameplayAbility::UGEGameplayAbility()
{
    // 기본 인스턴싱 정책 설정
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    /* 태그 설정 */
    using namespace GEGameplayTags;

    // 기본 어빌리티 태그 설정
    AbilityTags.AddTagFast(Action::Action);
    ActivationOwnedTags.AddTagFast(Action::Action);

    // ActivationBlockedTags 설정
    ActivationBlockedTags.AddTagFast(State::Dead);
    ActivationBlockedTags.AddTagFast(State::Knockdown);
    ActivationBlockedTags.AddTagFast(State::Stun);
}

void UGEGameplayAbility::InputReleased(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    Super::InputReleased(Handle, ActorInfo, ActivationInfo);

    // 어빌리티 입력이 비활성화되면 어빌리티를 종료합니다.
    if(bIsActive) EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGEGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    // Input Release 외의 조건으로 인해 어빌리티가 종료되는 경우 Input Release 상태로 자동 변경
    GetCurrentAbilitySpec()->InputPressed = false;
}
