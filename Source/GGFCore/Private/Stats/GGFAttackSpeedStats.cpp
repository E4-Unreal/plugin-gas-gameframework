// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/GGFAttackSpeedStats.h"

void UGGFAttackSpeedStats::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 공격 속도
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX(AttackSpeed)
}

void UGGFAttackSpeedStats::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::ClampAttributes(Attribute, NewValue);

    // 공격 속도
    CLAMP_ATTRIBUTE_AND_MAX_ATTRIBUTE(Attribute, NewValue, AttackSpeed)
}

void UGGFAttackSpeedStats::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::AdjustAttributes(Attribute, OldValue, NewValue);

    // 공격 속도
    ADJUST_ATTRIBUTE_FOR_MAX_ATTRIBUTE_CHANGE(AttackSpeed)
}

void UGGFAttackSpeedStats::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(AttackSpeed);
}

void UGGFAttackSpeedStats::OnRep_MaxAttackSpeed(const FGameplayAttributeData& OldMaxAttackSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MaxAttackSpeed);
}
