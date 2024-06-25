// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GGFGameMode.generated.h"

/**
 * GASGameFramework 플러그인 전용 게임 모드
 */
UCLASS()
class GGFPLAYERSYSTEM_API AGGFGameMode : public AGameMode
{
    GENERATED_BODY()

protected:
    // true 설정 시 모든 플레이어는 동일한 팀으로 취급됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bAllPlayerSameTeam = false;

public:
    AGGFGameMode();

    /* GameMode */

    virtual void PostLogin(APlayerController* NewPlayer) override;
};
