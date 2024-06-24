// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/GGFGE_Heal.h"

#include "Attributes/GEHealthAttributes.h"
#include "GGFCombatGameplayTags.h"

UGGFGE_Heal::UGGFGE_Heal()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo HealthModifier;
    HealthModifier.Attribute = UGEHealthAttributes::GetHealthAttribute();
    HealthModifier.ModifierOp = EGameplayModOp::Additive;
    HealthModifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(50);
    int32 Index = Modifiers.Emplace(HealthModifier);
    HealthModifierPtr = &Modifiers[Index];

    FGameplayEffectCue GameplayEffectCue;
    GameplayEffectCue.GameplayCueTags.AddTagFast(GameplayCue::Buff::Attribute::Heal);
    GameplayCues.Emplace(GameplayEffectCue);
}

void UGGFGE_Heal::SetHealMagnitude(float NewMagnitude)
{
    if(HealthModifierPtr)
    {
        HealthModifierPtr->ModifierMagnitude = FGameplayEffectModifierMagnitude(NewMagnitude);
    }
}
