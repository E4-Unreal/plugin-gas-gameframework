// Fill out your copyright notice in the Description page of Project Settings.

#include "Lobby/GGFLobbyGameMode.h"

#include "Lobby/GGFLobbyGameState.h"
#include "Lobby/GGFLobbyPlayerController.h"
#include "Lobby/GGFLobbyPlayerState.h"

AGGFLobbyGameMode::AGGFLobbyGameMode()
{
    GameStateClass = AGGFLobbyGameState::StaticClass();
    PlayerStateClass = AGGFLobbyPlayerState::StaticClass();
    PlayerControllerClass = AGGFLobbyPlayerController::StaticClass();
}
