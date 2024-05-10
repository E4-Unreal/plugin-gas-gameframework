// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/GEStaminaAttributes.h"

void UGEStaminaAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 스태미나
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX_AND_REGGFNRATE(Stamina)
}

void UGEStaminaAttributes::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::ClampAttributes(Attribute, NewValue);

    // 스태미나
    CLAMP_ATTRIBUTE_AND_MAX_ATTRIBUTE(Attribute, NewValue, Stamina)
}

void UGEStaminaAttributes::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::AdjustAttributes(Attribute, OldValue, NewValue);

    // 스태미나
    ADJUST_ATTRIBUTE_FOR_MAX_ATTRIBUTE_CHANGE(Stamina)
}

void UGEStaminaAttributes::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(Stamina);
}

void UGEStaminaAttributes::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MaxStamina);
}

void UGEStaminaAttributes::OnRep_StaminaRegenRate(const FGameplayAttributeData& OldStaminaRegenRate)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(StaminaRegenRate);
}
