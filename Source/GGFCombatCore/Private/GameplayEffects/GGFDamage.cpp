// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/GGFDamage.h"

#include "GameplayEffects/Calculations/GGFDamageCalculation.h"

UGGFDamage::UGGFDamage()
{
    /* 기본 Execution 설정 */
    Executions.Reset();
    FGameplayEffectExecutionDefinition ExecutionDefinition;
    ExecutionDefinition.CalculationClass = UGGFDamageCalculation::StaticClass(); // 기본 데미지 계산식
    Executions.Emplace(ExecutionDefinition);
}
