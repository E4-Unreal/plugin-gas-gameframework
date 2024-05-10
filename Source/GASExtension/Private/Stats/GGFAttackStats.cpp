﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "..\..\Public\Stats\GEAttackStats.h"

void UGGFAttackStats::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 공격력
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX(Attack)
}

void UGGFAttackStats::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::ClampAttributes(Attribute, NewValue);

    // 공격력
    CLAMP_ATTRIBUTE_AND_MAX_ATTRIBUTE(Attribute, NewValue, Attack)
}

void UGGFAttackStats::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::AdjustAttributes(Attribute, OldValue, NewValue);

    // 공격력
    ADJUST_ATTRIBUTE_FOR_MAX_ATTRIBUTE_CHANGE(Attack)
}

void UGGFAttackStats::OnRep_Attack(const FGameplayAttributeData& OldAttack)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(Attack);
}

void UGGFAttackStats::OnRep_MaxAttack(const FGameplayAttributeData& OldMaxAttack)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MaxAttack);
}
