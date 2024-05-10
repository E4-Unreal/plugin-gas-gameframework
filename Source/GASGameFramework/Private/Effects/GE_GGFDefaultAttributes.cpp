// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/GE_GGFDefaultAttributes.h"

#include "Attributes/GEHealthAttributes.h"
#include "Attributes/GEManaAttributes.h"
#include "Attributes/GEShieldAttributes.h"
#include "Attributes/GEStaminaAttributes.h"

UGE_GGFDefaultAttributes::UGE_GGFDefaultAttributes()
{
    // UGGFAttributeSetBase::AdjustAttributeForMaxChange 덕분에 Attribute 값이 Max 값으로 초기화됩니다.

    /* 기본값 설정 */
    const float DefaultValue = 100.f;

    /* Modifiers 설정 */
    // 체력
    const FGameplayModifierInfo MaxHealthModifier
    {
        UGEHealthAttributes::GetMaxHealthAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(DefaultValue))
    };

    // 실드
    const FGameplayModifierInfo MaxShieldModifier
    {
        UGEShieldAttributes::GetMaxShieldAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(DefaultValue))
    };

    // 마나
    const FGameplayModifierInfo MaxManaModifier
    {
        UGEManaAttributes::GetMaxManaAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(DefaultValue))
    };

    // 스태미나
    const FGameplayModifierInfo MaxStaminaModifier
    {
        UGEStaminaAttributes::GetMaxStaminaAttribute(),
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
