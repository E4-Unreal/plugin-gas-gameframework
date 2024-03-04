// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/GE_GEHealthAttributes.h"

#include "Attributes/GEHealthAttributes.h"

UGE_GEHealthAttributes::UGE_GEHealthAttributes()
{
    /* 기본값 설정 */
    // 체력
    const float MaxHealth = 100.f;
    const float HealthRatio = 1.f;

    /* Modifiers 설정 */
    // 최대 체력
    const FGameplayModifierInfo MaxHealthModifier
    {
        UGEHealthAttributes::GetMaxHealthAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(MaxHealth))
    };

    // 체력
    const FGameplayModifierInfo HealthModifier
    {
        UGEHealthAttributes::GetHealthAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(MaxHealth * HealthRatio))
    };

    /* Modifiers 추가 */
    Modifiers.Add(MaxHealthModifier);
    Modifiers.Add(HealthModifier);

    /* 기타 옵션 설정 */
    DurationPolicy = EGameplayEffectDurationType::Instant;
}
