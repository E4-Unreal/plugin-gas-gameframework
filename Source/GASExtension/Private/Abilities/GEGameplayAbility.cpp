// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GEGameplayAbility.h"

#include "GEGameplayTags.h"

UGEGameplayAbility::UGEGameplayAbility()
{
    /* 정책 설정 */

    // 인스턴싱 정책
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    // 실행 정책
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;

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
