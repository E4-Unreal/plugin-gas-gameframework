// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDamage.h"
#include "GGFStatDamage.generated.h"

/**
 * 스탯 데미지 전용 게임플레이 이펙트
 */
UCLASS()
class GGFCORE_API UGGFStatDamage : public UGGFDamage
{
    GENERATED_BODY()

public:
    UGGFStatDamage();
};
