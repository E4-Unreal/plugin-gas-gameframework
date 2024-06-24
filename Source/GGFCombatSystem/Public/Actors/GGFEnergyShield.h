// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDestructibleActor.h"
#include "GGFEnergyShield.generated.h"

/**
 * 적의 공격을 막아주는 에너지 실드입니다.
 * 일정 데미지를 입으면 파괴됩니다.
 */
UCLASS()
class GGFCOMBATSYSTEM_API AGGFEnergyShield : public AGGFDestructibleActor
{
    GENERATED_BODY()

public:
    AGGFEnergyShield(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
