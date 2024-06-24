// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/GEDefenseStats.h"

void UGEDefenseStats::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 방어력
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX(Defense)
}

void UGEDefenseStats::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::ClampAttributes(Attribute, NewValue);

    // 방어력
    CLAMP_ATTRIBUTE_AND_MAX_ATTRIBUTE(Attribute, NewValue, Defense)
}

void UGEDefenseStats::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::AdjustAttributes(Attribute, OldValue, NewValue);

    // 방어력
    ADJUST_ATTRIBUTE_FOR_MAX_ATTRIBUTE_CHANGE(Defense)
}

void UGEDefenseStats::OnRep_Defense(const FGameplayAttributeData& OldDefense)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(Defense);
}

void UGEDefenseStats::OnRep_MaxDefense(const FGameplayAttributeData& OldMaxDefense)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MaxDefense);
}
