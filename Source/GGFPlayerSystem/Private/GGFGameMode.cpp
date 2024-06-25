// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFGameMode.h"

#include "GGFGameState.h"
#include "GGFPlayerState.h"
#include "GameFramework/GameState.h"

AGGFGameMode::AGGFGameMode()
{
    PlayerStateClass = AGGFPlayerState::StaticClass();
    GameStateClass = AGGFGameState::StaticClass();
}

void AGGFGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    if(bAllPlayerSameTeam)
    {
        if(auto PlayerState = NewPlayer->GetPlayerState<APlayerState>())
        {
            if(PlayerState->Implements<UGGFTeamInterface>())
            {
                IGGFTeamInterface::Execute_SetTeamID(PlayerState, 0);
            }
        }
    }
}
