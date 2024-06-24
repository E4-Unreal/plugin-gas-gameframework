// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GGFEffectArea.h"
#include "GGFHealArea.generated.h"

/**
 * 범위 안에 들어가 있는 대상에게 지속 힐 버프를 걸어주는 힐 장판 액터 클래스
 */
UCLASS()
class GGFCOMBATSYSTEM_API AGGFHealArea : public AGGFEffectArea
{
    GENERATED_BODY()

public:
    AGGFHealArea();
};
