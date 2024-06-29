// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/GGFStatDamage.h"

#include "GameplayEffects/Calculations/GGFStatDamageCalculation.h"

UGGFStatDamage::UGGFStatDamage()
{
    ExecutionDefinitionPtr->CalculationClass = UGGFStatDamageCalculation::StaticClass();
}
