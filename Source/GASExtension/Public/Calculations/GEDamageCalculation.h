// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEDamageCalculation.generated.h"

/**
 * 가장 기본적인 데미지 계산식입니다.
 * 총 데미지: 공격 주체의 공격력 - 공격 대상의 방어력
 * 데미지 계산: (공격 대상의 체력 + 방어막) - 데미지
 * 방어막 수치가 먼저 소모되며 0 도달 이후 체력 수치가 소모됩니다.
 */
UCLASS()
class GASEXTENSION_API UGEDamageCalculation : public UGameplayEffectExecutionCalculation
{
    GENERATED_BODY()

public:
    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
