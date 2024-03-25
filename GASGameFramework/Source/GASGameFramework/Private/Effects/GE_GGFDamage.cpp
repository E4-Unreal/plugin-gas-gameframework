// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/GE_GGFDamage.h"

#include "Attributes/GGFHealthAttributes.h"

UGE_GGFDamage::UGE_GGFDamage()
{
    /* 기본값 설정 */
    const float Damage = 20.f;

    /* Modifiers 설정 */
    const FGameplayModifierInfo DamageModifier
    {
        UGGFHealthAttributes::GetDamageAttribute(),
        EGameplayModOp::Additive,
        FGameplayEffectModifierMagnitude(FScalableFloat(Damage))
    };

    /* Modifiers 추가 */
    Modifiers.Add(DamageModifier);

    /* 기타 옵션 설정 */
    DurationPolicy = EGameplayEffectDurationType::Instant;
}
