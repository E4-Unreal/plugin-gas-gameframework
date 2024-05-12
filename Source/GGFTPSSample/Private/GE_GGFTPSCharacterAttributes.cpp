// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_GGFTPSCharacterAttributes.h"

#include "Attributes/GEHealthAttributes.h"
#include "Attributes/GEShieldAttributes.h"

UGE_GGFTPSCharacterAttributes::UGE_GGFTPSCharacterAttributes()
{
    /* Modifiers 설정 */
    // 체력
    const float MaxHealth = 100;
    const FGameplayModifierInfo MaxHealthModifier
    {
        UGEHealthAttributes::GetMaxHealthAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(MaxHealth))
    };

    const FGameplayModifierInfo HealthModifier
    {
        UGEHealthAttributes::GetHealthAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(MaxHealth))
    };

    // 실드
    const float MaxShield = 100;
    const FGameplayModifierInfo MaxShieldModifier
    {
        UGEShieldAttributes::GetMaxShieldAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(MaxShield))
    };

    const FGameplayModifierInfo ShieldModifier
    {
        UGEShieldAttributes::GetShieldAttribute(),
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
