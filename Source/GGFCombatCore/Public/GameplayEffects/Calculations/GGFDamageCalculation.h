// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASExtension/Public/GameplayEffects/Calculations/GEDamageCalculation.h"
#include "GGFDamageCalculation.generated.h"

/**
 * GASGameFramework 전용 데미지 계산식
 */
UCLASS()
class GGFCOMBATCORE_API UGGFDamageCalculation : public UGEDamageCalculation
{
    GENERATED_BODY()

public:
    UGGFDamageCalculation();
};
