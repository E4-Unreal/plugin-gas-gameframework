// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/GGFGE_Buff.h"

#include "Stats/GGFAttackStats.h"
#include "Stats/GGFDefenseStats.h"
#include "Stats/GGFAttackSpeedStats.h"
#include "Stats/GGFMoveSpeedStats.h"
#include "Stats/GGFAbilityHasteStats.h"

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
    SetModifier(UGGFAttackStats::GetAttackAttribute(), AttackModifierPtr, ModifierOp, Magnitude);
}

void UGGFGE_Buff::SetDefenseModifier(EGameplayModOp::Type ModifierOp, float Magnitude)
{
    SetModifier(UGGFDefenseStats::GetDefenseAttribute(), DefenseModifierPtr, ModifierOp, Magnitude);
}

void UGGFGE_Buff::SetAttackSpeedModifier(EGameplayModOp::Type ModifierOp, float Magnitude)
{
    SetModifier(UGGFAttackSpeedStats::GetAttackSpeedAttribute(), AttackSpeedModifierPtr, ModifierOp, Magnitude);
}

void UGGFGE_Buff::SetMoveSpeedModifier(EGameplayModOp::Type ModifierOp, float Magnitude)
{
    SetModifier(UGGFMoveSpeedStats::GetMoveSpeedAttribute(), MoveSpeedModifierPtr, ModifierOp, Magnitude);
}

void UGGFGE_Buff::SetAbilityHasteModifier(EGameplayModOp::Type ModifierOp, float Magnitude)
{
    SetModifier(UGGFAbilityHasteStats::GetAbilityHasteAttribute(), AbilityHasteModifierPtr, ModifierOp, Magnitude);
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
