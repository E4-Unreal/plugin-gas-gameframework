// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFTickEffect.h"
#include "GGFTickDamage.generated.h"

/**
 * 틱 데미지 전용 게임플레이 이펙트 클래스
 */
UCLASS()
class GGFCORE_API UGGFTickDamage : public UGGFTickEffect
{
    GENERATED_BODY()

protected:
    FGameplayModifierInfo* DamageModifierPtr;

public:
    UGGFTickDamage();
};
