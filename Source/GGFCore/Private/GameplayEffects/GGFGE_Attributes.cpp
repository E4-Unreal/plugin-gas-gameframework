// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/GGFGE_Attributes.h"

#include "GGFGameplayTags.h"
#include "Attributes/GGFHealthAttributes.h"
#include "Attributes/GGFManaAttributes.h"
#include "Attributes/GGFShieldAttributes.h"
#include "Attributes/GGFStaminaAttributes.h"

UGGFGE_Attributes::UGGFGE_Attributes()
{
    SET_ATTRIBUTE_MODIFIER(UGGFHealthAttributes, Health);
    SET_ATTRIBUTE_MODIFIER(UGGFManaAttributes, Mana);
    SET_ATTRIBUTE_MODIFIER(UGGFShieldAttributes, Shield);
    SET_ATTRIBUTE_MODIFIER(UGGFStaminaAttributes, Stamina);
}
