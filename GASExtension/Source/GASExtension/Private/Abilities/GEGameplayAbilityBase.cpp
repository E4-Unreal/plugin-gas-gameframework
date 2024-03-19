// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GEGameplayAbilityBase.h"

#include "GEGameplayTags.h"
#include "Attributes/GEHealthAttributes.h"

UGEGameplayAbilityBase::UGEGameplayAbilityBase()
{
    // 기본 인스턴싱 정책 설정
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    // 기본 Blocking 태그 설정
    ActivationBlockedTags.AddTag(GEGameplayTags::State::DeadTag);
    ActivationBlockedTags.AddTag(GEGameplayTags::State::KnockdownTag);
    ActivationBlockedTags.AddTag(GEGameplayTags::State::StunTag);
}

const FGameplayTag UGEGameplayAbilityBase::GetInputTag_Implementation() const
{
    return InputTag;
}
