// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFGameModeInterface.generated.h"

UINTERFACE()
class GGFCORE_API UGGFGameModeInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * GASGameFramework 플러그인 전용 게임 모드 인터페이스
 */
class GGFCORE_API IGGFGameModeInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetViewTargetToNextPlayer(APlayerController* PlayerController);
};
