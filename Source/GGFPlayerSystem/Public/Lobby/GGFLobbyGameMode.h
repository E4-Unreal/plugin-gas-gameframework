// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGameMode.h"
#include "GGFLobbyGameMode.generated.h"

/**
 * 로비 전용 게임 모드
 *
 * - 호스트 플레이어가 존재합니다.
 * - 게스트 플레이어는 자동으로 호스트 플레이어 팀으로 설정됩니다.
 */
UCLASS()
class GGFPLAYERSYSTEM_API AGGFLobbyGameMode : public AGGFGameMode
{
    GENERATED_BODY()

public:
    AGGFLobbyGameMode();
};
