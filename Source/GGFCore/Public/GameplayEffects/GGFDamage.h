// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGameplayEffect.h"
#include "GGFDamage.generated.h"

class UTargetTagRequirementsGameplayEffectComponent;

/**
 * 일반 데미지 전용 게임플레이 이펙트
 */
UCLASS()
class GGFCORE_API UGGFDamage : public UGGFGameplayEffect
{
    GENERATED_BODY()

protected:
    FGameplayEffectExecutionDefinition* ExecutionDefinitionPtr;
    FGameplayModifierInfo* DamageModifierPtr;

public:
    UGGFDamage(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
