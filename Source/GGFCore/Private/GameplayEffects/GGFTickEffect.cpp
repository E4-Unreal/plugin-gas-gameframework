// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/GGFTickEffect.h"

#include "GameplayEffectComponents/TargetTagRequirementsGameplayEffectComponent.h"
#include "GGFGameplayTags.h"

UGGFTickEffect::UGGFTickEffect()
{
    // Duration 정책 설정
    DurationPolicy = EGameplayEffectDurationType::HasDuration;
    DurationMagnitude = FGameplayEffectModifierMagnitude(2);
    Period = 1;

    // Stack 정책 설정
    StackingType = EGameplayEffectStackingType::AggregateByTarget;
    StackLimitCount = 1;
    StackDurationRefreshPolicy = EGameplayEffectStackingDurationPolicy::RefreshOnSuccessfulApplication;
    StackPeriodResetPolicy = EGameplayEffectStackingPeriodPolicy::NeverReset;
    StackExpirationPolicy = EGameplayEffectStackingExpirationPolicy::ClearEntireStack;

    // 무시 태그 설정
    GetOrFindTargetTagRequirementsComponent()->OngoingTagRequirements.IgnoreTags.AddTagFast(State::Dead);
}
