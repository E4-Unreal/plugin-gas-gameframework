// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/GGFDefenseStats.h"

void UGGFDefenseStats::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 방어력
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX(Defense)
}

void UGGFDefenseStats::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::ClampAttributes(Attribute, NewValue);

    // 방어력
    CLAMP_ATTRIBUTE_AND_MAX_ATTRIBUTE(Attribute, NewValue, Defense)
}

void UGGFDefenseStats::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::AdjustAttributes(Attribute, OldValue, NewValue);

    // 방어력
    ADJUST_ATTRIBUTE_FOR_MAX_ATTRIBUTE_CHANGE(Defense)
}

void UGGFDefenseStats::OnRep_Defense(const FGameplayAttributeData& OldDefense)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(Defense);
}

void UGGFDefenseStats::OnRep_MaxDefense(const FGameplayAttributeData& OldMaxDefense)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MaxDefense);
}
