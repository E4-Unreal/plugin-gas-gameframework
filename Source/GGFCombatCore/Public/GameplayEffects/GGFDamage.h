// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffects/GEDamageBase.h"
#include "GGFDamage.generated.h"

/**
 * GASGameFramework 데미지 전용 게임플레이 이펙트 클래스
 */
UCLASS()
class GGFCOMBATCORE_API UGGFDamage : public UGEDamageBase
{
    GENERATED_BODY()

public:
    UGGFDamage();
};
