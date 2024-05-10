// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/GEAbilityHasteStats.h"

void UGEAbilityHasteStats::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 스킬 가속
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX(AbilityHaste)
}

void UGEAbilityHasteStats::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::ClampAttributes(Attribute, NewValue);

    // 스킬 가속
    CLAMP_ATTRIBUTE_AND_MAX_ATTRIBUTE(Attribute, NewValue, AbilityHaste)
}

void UGEAbilityHasteStats::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::AdjustAttributes(Attribute, OldValue, NewValue);

    // 스킬 가속
    ADJUST_ATTRIBUTE_FOR_MAX_ATTRIBUTE_CHANGE(AbilityHaste)
}

void UGEAbilityHasteStats::OnRep_AbilityHaste(const FGameplayAttributeData& OldAbilityHaste)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(AbilityHaste);
}

void UGEAbilityHasteStats::OnRep_MaxAbilityHaste(const FGameplayAttributeData& OldMaxAbilityHaste)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MaxAbilityHaste);
}
