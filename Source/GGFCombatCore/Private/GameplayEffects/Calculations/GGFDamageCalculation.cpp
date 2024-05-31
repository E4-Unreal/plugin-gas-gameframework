// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/Calculations/GGFDamageCalculation.h"

#include "GGFCombatGameplayTags.h"

using namespace GGFGameplayTags;

UGGFDamageCalculation::UGGFDamageCalculation()
{
    DamageImmunityMap.Emplace(Damage::Type::Physical, Buff::Immunity::Physical);
    DamageImmunityMap.Emplace(Damage::Type::Fire, Buff::Immunity::Fire);
    DamageImmunityMap.Emplace(Damage::Type::Water, Buff::Immunity::Water);
    DamageImmunityMap.Emplace(Damage::Type::Electricity, Buff::Immunity::Electricity);
    DamageImmunityMap.Emplace(Damage::Type::Ice, Buff::Immunity::Ice);
}
