// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/GEDamageBase.h"

#include "GGFGameplayTags.h"
#include "GameplayEffects/Calculations/GEDamageCalculation.h"
#include "GameplayEffectComponents/TargetTagRequirementsGameplayEffectComponent.h"



FName UGEDamageBase::TargetTagRequirementsComponentName(TEXT("TargetTagRequirements"));

UGEDamageBase::UGEDamageBase(const FObjectInitializer& ObjectInitializer)
{
    /* TargetTagRequirements */
    TargetTagRequirementsComponent = CreateDefaultSubobject<UTargetTagRequirementsGameplayEffectComponent>(TargetTagRequirementsComponentName);

    // 데미지 무시
    FGameplayTagContainer& IgnoreTagContainer = TargetTagRequirementsComponent->ApplicationTagRequirements.IgnoreTags;
    IgnoreTagContainer.AddLeafTag(State::Invinsible); // 무적 상태
    IgnoreTagContainer.AddLeafTag(State::Dead); // 이미 죽은 상태

    GEComponents.Emplace(TargetTagRequirementsComponent);

    /* 기본 Execution 설정 */
    FGameplayEffectExecutionDefinition ExecutionDefinition;
    ExecutionDefinition.CalculationClass = UGEDamageCalculation::StaticClass(); // 기본 데미지 계산식
    Executions.Emplace(ExecutionDefinition);
}
