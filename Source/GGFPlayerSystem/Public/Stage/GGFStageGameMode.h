// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGameMode.h"
#include "GGFStageGameMode.generated.h"

/**
 * 스테이지 전용 게임 모드
 */
UCLASS()
class GGFPLAYERSYSTEM_API AGGFStageGameMode : public AGGFGameMode
{
    GENERATED_BODY()

public:
    AGGFStageGameMode();
};
