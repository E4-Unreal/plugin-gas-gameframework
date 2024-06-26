// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/GGFDamageBase.h"

#include "GGFGameplayTags.h"
#include "GameplayEffectComponents/TargetTagRequirementsGameplayEffectComponent.h"
#include "GameplayEffects/Calculations/GGFDamageCalculation.h"

UGGFDamageBase::UGGFDamageBase(const FObjectInitializer& ObjectInitializer)
{
    // 데미지 무시
    FGameplayTagContainer& IgnoreTagContainer = GetOrFindTargetTagRequirementsComponent()->ApplicationTagRequirements.IgnoreTags;
    IgnoreTagContainer.AddLeafTag(State::Buff::Invinsible); // 무적 상태

    /* 기본 데미지 계산식 설정 */
    FGameplayEffectExecutionDefinition ExecutionDefinition;
    ExecutionDefinition.CalculationClass = UGGFDamageCalculation::StaticClass();
    Executions.Emplace(ExecutionDefinition);
}
