// Fill out your copyright notice in the Description page of Project Settings.

#include "Attributes/GGFShieldAttributes.h"

void UGGFShieldAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 방어막
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX_AND_REGGFNRATE(Shield)
}

void UGGFShieldAttributes::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::ClampAttributes(Attribute, NewValue);

    // 방어막
    CLAMP_ATTRIBUTE_AND_MAX_ATTRIBUTE(Attribute, NewValue, Shield)
}

void UGGFShieldAttributes::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::AdjustAttributes(Attribute, OldValue, NewValue);

    // 방어막
    ADJUST_ATTRIBUTE_FOR_MAX_ATTRIBUTE_CHANGE(Shield)
}

void UGGFShieldAttributes::OnRep_Shield(const FGameplayAttributeData& OldShield)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(Shield);
}

void UGGFShieldAttributes::OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MaxShield);
}

void UGGFShieldAttributes::OnRep_ShieldRegenRate(const FGameplayAttributeData& OldShieldRegenRate)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(ShieldRegenRate);
}
