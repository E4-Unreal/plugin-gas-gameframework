// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/GGFMoveSpeedStats.h"

void UGGFMoveSpeedStats::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 이동 속도
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX(MoveSpeed)
}

void UGGFMoveSpeedStats::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::ClampAttributes(Attribute, NewValue);

    // 이동 속도
    CLAMP_ATTRIBUTE_AND_MAX_ATTRIBUTE(Attribute, NewValue, MoveSpeed)
}

void UGGFMoveSpeedStats::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::AdjustAttributes(Attribute, OldValue, NewValue);

    // 이동 속도
    ADJUST_ATTRIBUTE_FOR_MAX_ATTRIBUTE_CHANGE(MoveSpeed)
}

void UGGFMoveSpeedStats::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MoveSpeed);
}

void UGGFMoveSpeedStats::OnRep_MaxMoveSpeed(const FGameplayAttributeData& OldMaxMoveSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MaxMoveSpeed);
}
