﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/GGF_GGFTickDamage.h"

#include "Attributes/GGFHealthAttributes.h"

UGGF_GGFTickDamage::UGGF_GGFTickDamage()
{
    /* 기본값 설정 */
    const float Damage = 4.f;
    const float Duration = 4.f;
    const float TickTime = 1.f;

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
    DurationPolicy = EGameplayEffectDurationType::HasDuration;
    DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(Duration));
    Period = TickTime;
}
