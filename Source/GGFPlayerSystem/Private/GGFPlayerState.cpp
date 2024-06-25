// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFPlayerState.h"

#include "Logging.h"
#include "Net/UnrealNetwork.h"

void AGGFPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, TeamID)
}

void AGGFPlayerState::SetTeamID_Implementation(uint8 NewTeamID)
{
#if WITH_EDITOR
    LOG_ACTOR_DETAIL(Log, TEXT("OldTeamID: %d, NewTeamID: %d"), TeamID, NewTeamID)
#endif

    TeamID = NewTeamID;
}

void AGGFPlayerState::OnRep_TeamID(uint8 OldTeamID)
{
#if WITH_EDITOR
    LOG_ACTOR_DETAIL(Log, TEXT("OldTeamID: %d, NewTeamID: %d"), OldTeamID, TeamID)
#endif
}
