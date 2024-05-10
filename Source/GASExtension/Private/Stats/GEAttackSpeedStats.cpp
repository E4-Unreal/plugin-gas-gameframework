// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/GEAttackSpeedStats.h"

void UGEAttackSpeedStats::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 공격 속도
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX(AttackSpeed)
}

void UGEAttackSpeedStats::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::ClampAttributes(Attribute, NewValue);

    // 공격 속도
    CLAMP_ATTRIBUTE_AND_MAX_ATTRIBUTE(Attribute, NewValue, AttackSpeed)
}

void UGEAttackSpeedStats::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::AdjustAttributes(Attribute, OldValue, NewValue);

    // 공격 속도
    ADJUST_ATTRIBUTE_FOR_MAX_ATTRIBUTE_CHANGE(AttackSpeed)
}

void UGEAttackSpeedStats::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(AttackSpeed);
}

void UGEAttackSpeedStats::OnRep_MaxAttackSpeed(const FGameplayAttributeData& OldMaxAttackSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MaxAttackSpeed);
}
