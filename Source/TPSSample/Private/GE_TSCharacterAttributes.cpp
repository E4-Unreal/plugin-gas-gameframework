// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_TSCharacterAttributes.h"

#include "Attributes/GGFHealthAttributes.h"
#include "Attributes/GGFShieldAttributes.h"

UGE_TSCharacterAttributes::UGE_TSCharacterAttributes()
{
    /* Modifiers 설정 */
    // 체력
    const float MaxHealth = 100;
    const FGameplayModifierInfo MaxHealthModifier
    {
        UGGFHealthAttributes::GetMaxHealthAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(MaxHealth))
    };

    const FGameplayModifierInfo HealthModifier
    {
        UGGFHealthAttributes::GetHealthAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(MaxHealth))
    };

    // 실드
    const float MaxShield = 100;
    const FGameplayModifierInfo MaxShieldModifier
    {
        UGGFShieldAttributes::GetMaxShieldAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(MaxShield))
    };

    const FGameplayModifierInfo ShieldModifier
    {
        UGGFShieldAttributes::GetShieldAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(MaxShield))
    };

    /* Modifiers 추가 */
    Modifiers.Add(MaxHealthModifier);
    Modifiers.Add(HealthModifier);
    Modifiers.Add(MaxShieldModifier);
    Modifiers.Add(ShieldModifier);

    /* 기타 옵션 설정 */
    DurationPolicy = EGameplayEffectDurationType::Instant;
}
