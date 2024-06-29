// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDamageCalculation.h"
#include "GGFStatDamageCalculation.generated.h"

/**
 * 스탯 기반 데미지 계산식
 */
UCLASS()
class GGFCORE_API UGGFStatDamageCalculation : public UGGFDamageCalculation
{
    GENERATED_BODY()

protected:
    /* GGFDamageCalculation */

    virtual float CalculateTotalDamage(const FGameplayEffectCustomExecutionParameters& ExecutionParams, UAbilitySystemComponent* SourceSystem, UAbilitySystemComponent* TargetSystem) const override;
};
