// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGameplayEffect.h"
#include "GGFTickEffect.generated.h"

/**
 * 기본적인 틱 전용 게임플레이 이펙트입니다.
 */
UCLASS()
class GGFCORE_API UGGFTickEffect : public UGGFGameplayEffect
{
    GENERATED_BODY()

public:
    UGGFTickEffect();
};
