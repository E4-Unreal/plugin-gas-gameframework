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

void AGGFLobbyGameMode::OnPostLogin(AController* NewPlayer)
{
    Super::OnPostLogin(NewPlayer);

    if(auto NewPlayerState = NewPlayer->GetPlayerState<AGGFPlayerState>())
    {
        // 호스트 설정
        if(NumPlayers == 1) NewPlayerState->SetHost(true);

        // 팀 정보 설정
        FGGFTeamInfo NewTeamInfo;
        NewTeamInfo.TeamID = 0;
        NewTeamInfo.MemberID = NumPlayers - 1;
        NewPlayerState->SetTeamInfo(NewTeamInfo);
    }
}
