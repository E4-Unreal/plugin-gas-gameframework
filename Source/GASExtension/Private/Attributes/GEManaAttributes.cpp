// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/GEManaAttributes.h"

void UGEManaAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 마나
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX_AND_REGGFNRATE(Mana)
}

void UGEManaAttributes::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::ClampAttributes(Attribute, NewValue);

    // 마나
    CLAMP_ATTRIBUTE_AND_MAX_ATTRIBUTE(Attribute, NewValue, Mana)
}

void UGEManaAttributes::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::AdjustAttributes(Attribute, OldValue, NewValue);

    // 마나
    ADJUST_ATTRIBUTE_FOR_MAX_ATTRIBUTE_CHANGE(Mana)
}

void UGEManaAttributes::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(Mana);
}

void UGEManaAttributes::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MaxMana);
}

void UGEManaAttributes::OnRep_ManaRegenRate(const FGameplayAttributeData& OldManaRegenRate)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(ManaRegenRate);
}
