// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GEGameplayAbilityBase.h"

#include "GEGameplayTags.h"
#include "Attributes/GEHealthAttributes.h"

UGEGameplayAbilityBase::UGEGameplayAbilityBase()
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

const FGameplayTag UGEGameplayAbilityBase::GetInputTag_Implementation() const
{
    return InputTag;
}
