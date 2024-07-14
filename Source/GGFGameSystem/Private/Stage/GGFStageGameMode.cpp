// Fill out your copyright notice in the Description page of Project Settings.

#include "Stage/GGFStageGameMode.h"

#include "Stage/GGFStageGameState.h"
#include "Stage/GGFStagePlayerController.h"
#include "Stage/GGFStagePlayerState.h"

AGGFStageGameMode::AGGFStageGameMode()
{
    GameStateClass = AGGFStageGameState::StaticClass();
    PlayerStateClass = AGGFStagePlayerState::StaticClass();
    PlayerControllerClass = AGGFStagePlayerController::StaticClass();
}
