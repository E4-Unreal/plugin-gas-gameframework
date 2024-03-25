// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/GE_GETickDamageWithHealthRatio.h"

#include "Attributes/GEHealthAttributes.h"

UGE_GETickDamageWithHealthRatio::UGE_GETickDamageWithHealthRatio()
{
    /* 기본값 설정 */
    const float Ratio = 0.1f;
    const float Duration = 4.f; // 0초, 1초, 2초, 3초, 4초 총 5 번 적용됩니다.
    const float TickTime = 1.f;

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
    DurationPolicy = EGameplayEffectDurationType::HasDuration;
    DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(Duration));
    Period = TickTime;
}
