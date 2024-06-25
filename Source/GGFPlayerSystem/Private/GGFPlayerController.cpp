// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFPlayerController.h"

#include "GameFramework/PlayerState.h"

uint8 AGGFPlayerController::GetTeamID_Implementation() const
{
    if(PlayerState->Implements<UGGFTeamInterface>())
    {
        return Execute_GetTeamID(PlayerState);
    }

    return NoTeam;
}

void AGGFPlayerController::SetTeamID_Implementation(uint8 NewTeamID)
{
    if(PlayerState->Implements<UGGFTeamInterface>())
    {
        return Execute_SetTeamID(PlayerState, NewTeamID);
    }
}
