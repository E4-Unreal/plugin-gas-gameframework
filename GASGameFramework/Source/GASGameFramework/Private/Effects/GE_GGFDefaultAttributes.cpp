// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/GGF_GGFDefaultAttributes.h"

#include "Attributes/GGFStaminaAttributes.h"

UGGF_GGFDefaultAttributes::UGGF_GGFDefaultAttributes()
{
    // UGGFAttributeSetBase::AdjustAttributeForMaxChange 덕분에 Attribute 값이 Max 값으로 초기화됩니다.

    /* 기본값 설정 */
    const float DefaultValue = 100.f;

    /* Modifiers 설정 */
    // 체력
    const FGameplayModifierInfo MaxHealthModifier
    {
        UGGFHealthAttributes::GetMaxHealthAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(DefaultValue))
    };

    // 실드
    const FGameplayModifierInfo MaxShieldModifier
    {
        UGGFShieldAttributes::GetMaxShieldAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(DefaultValue))
    };

    // 마나
    const FGameplayModifierInfo MaxManaModifier
    {
        UGGFManaAttributes::GetMaxManaAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(DefaultValue))
    };

    // 스태미나
    const FGameplayModifierInfo MaxStaminaModifier
    {
        UGGFStaminaAttributes::GetMaxStaminaAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(DefaultValue))
    };

    /* Modifiers 추가 */
    Modifiers.Add(MaxHealthModifier);
    Modifiers.Add(MaxShieldModifier);
    Modifiers.Add(MaxManaModifier);
    Modifiers.Add(MaxStaminaModifier);

    /* 기타 옵션 설정 */
    DurationPolicy = EGameplayEffectDurationType::Instant;
}
