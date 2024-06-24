// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/GGFGE_Buff.h"

#include "Stats/GEAttackStats.h"
#include "Stats/GEDefenseStats.h"
#include "Stats/GEAttackSpeedStats.h"
#include "Stats/GEMoveSpeedStats.h"
#include "Stats/GEAbilityHasteStats.h"

UGGFGE_Buff::UGGFGE_Buff()
{
    DurationPolicy = EGameplayEffectDurationType::HasDuration;
    DurationMagnitude = FGameplayEffectModifierMagnitude(5);

    StackingType = EGameplayEffectStackingType::AggregateByTarget;
    StackLimitCount = 1;
    StackDurationRefreshPolicy = EGameplayEffectStackingDurationPolicy::RefreshOnSuccessfulApplication;
    StackPeriodResetPolicy = EGameplayEffectStackingPeriodPolicy::NeverReset;
    StackExpirationPolicy = EGameplayEffectStackingExpirationPolicy::ClearEntireStack;
}

void UGGFGE_Buff::SetAttackModifier(EGameplayModOp::Type ModifierOp, float Magnitude)
{
    SetModifier(UGEAttackStats::GetAttackAttribute(), AttackModifierPtr, ModifierOp, Magnitude);
}

void UGGFGE_Buff::SetDefenseModifier(EGameplayModOp::Type ModifierOp, float Magnitude)
{
    SetModifier(UGEDefenseStats::GetDefenseAttribute(), DefenseModifierPtr, ModifierOp, Magnitude);
}

void UGGFGE_Buff::SetAttackSpeedModifier(EGameplayModOp::Type ModifierOp, float Magnitude)
{
    SetModifier(UGEAttackSpeedStats::GetAttackSpeedAttribute(), AttackSpeedModifierPtr, ModifierOp, Magnitude);
}

void UGGFGE_Buff::SetMoveSpeedModifier(EGameplayModOp::Type ModifierOp, float Magnitude)
{
    SetModifier(UGEMoveSpeedStats::GetMoveSpeedAttribute(), MoveSpeedModifierPtr, ModifierOp, Magnitude);
}

void UGGFGE_Buff::SetAbilityHasteModifier(EGameplayModOp::Type ModifierOp, float Magnitude)
{
    SetModifier(UGEAbilityHasteStats::GetAbilityHasteAttribute(), AbilityHasteModifierPtr, ModifierOp, Magnitude);
}

void UGGFGE_Buff::SetModifier(FGameplayAttribute Attribute, FGameplayModifierInfo*& ModifierPtr,
                              EGameplayModOp::Type ModifierOp, float Magnitude)
{
    if(ModifierPtr)
    {
        ModifierPtr->ModifierOp = ModifierOp;
        ModifierPtr->ModifierMagnitude = FGameplayEffectModifierMagnitude(Magnitude);
    }
    else
    {
        FGameplayModifierInfo NewModifier;
        NewModifier.Attribute = Attribute;
        NewModifier.ModifierOp = ModifierOp;
        NewModifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(Magnitude);
        int32 Index = Modifiers.Emplace(NewModifier);
        ModifierPtr = &Modifiers[Index];
    }
}
