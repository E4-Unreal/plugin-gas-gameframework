// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/GGFGE_ContinuousHeal.h"

UGGFGE_ContinuousHeal::UGGFGE_ContinuousHeal()
{
    DurationPolicy = EGameplayEffectDurationType::HasDuration;
    DurationMagnitude = FGameplayEffectModifierMagnitude(3);
    Period = 1;

    SetHealMagnitude(10);
}
