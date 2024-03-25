// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/GGFStaminaAttributes.h"

void UGGFStaminaAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 스태미나
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX_AND_REGGFNRATE(Stamina)
}

void UGGFStaminaAttributes::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::ClampAttributes(Attribute, NewValue);

    // 스태미나
    CLAMP_ATTRIBUTE_AND_MAX_ATTRIBUTE(Attribute, NewValue, Stamina)
}

void UGGFStaminaAttributes::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::AdjustAttributes(Attribute, OldValue, NewValue);

    // 스태미나
    ADJUST_ATTRIBUTE_FOR_MAX_ATTRIBUTE_CHANGGF(Stamina)
}

void UGGFStaminaAttributes::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(Stamina);
}

void UGGFStaminaAttributes::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MaxStamina);
}

void UGGFStaminaAttributes::OnRep_StaminaRegenRate(const FGameplayAttributeData& OldStaminaRegenRate)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(StaminaRegenRate);
}
