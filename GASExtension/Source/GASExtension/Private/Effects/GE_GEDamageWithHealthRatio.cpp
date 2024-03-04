// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/GE_GEDamageWithHealthRatio.h"

#include "AttributeSets/GEHealthAttributes.h"

UGE_GEDamageWithHealthRatio::UGE_GEDamageWithHealthRatio()
{
    /* 기본값 설정 */
    const float Ratio = 0.1f;

    /* Modifiers 설정 */
    FGameplayEffectAttributeCaptureDefinition MaxHealthAttribute;
    MaxHealthAttribute.AttributeToCapture = UGEHealthAttributes::GetMaxHealthAttribute();
    MaxHealthAttribute.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

    FAttributeBasedFloat DamageWithHealthRatio;
    DamageWithHealthRatio.Coefficient = Ratio;
    DamageWithHealthRatio.BackingAttribute = MaxHealthAttribute;

    const FGameplayModifierInfo DamageModifier
    {
        UGEHealthAttributes::GetDamageAttribute(),
        EGameplayModOp::Additive,
        FGameplayEffectModifierMagnitude(DamageWithHealthRatio)
    };

    /* Modifiers 추가 */
    Modifiers.Add(DamageModifier);

    /* 기타 옵션 설정 */
    DurationPolicy = EGameplayEffectDurationType::Instant;
}
