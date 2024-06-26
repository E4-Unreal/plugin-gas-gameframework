// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGameplayEffect.h"
#include "GGFDamage.generated.h"

class UTargetTagRequirementsGameplayEffectComponent;

/**
 * 데미지 전용 게임플레이 이펙트 클래스
 */
UCLASS()
class GGFCORE_API UGGFDamage : public UGGFGameplayEffect
{
    GENERATED_BODY()

protected:
    FGameplayModifierInfo* DamageModifierPtr;

public:
    UGGFDamage(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
