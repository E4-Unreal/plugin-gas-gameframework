// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFPlayerState.h"

#include "AbilitySystemGlobals.h"

UAbilitySystemComponent* AGGFPlayerState::GetAbilitySystemComponent() const
{
    return UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetPawn());
}

FGenericTeamId AGGFPlayerState::GetGenericTeamId() const
{
    if(auto GameState = GetWorld()->GetGameState<AGGFGameState>())
    {
        return GameState->GetTeamInfo(const_cast<AGGFPlayerState*>(this)).TeamID;
    }

    return FGenericTeamId::NoTeam;
}

void AGGFPlayerState::SetGenericTeamId(const FGenericTeamId& TeamID)
{
    if(auto GameState = GetWorld()->GetGameState<AGGFGameState>())
    {
        GameState->RemovePlayerFromTeam(this);
        GameState->AddPlayerToTeam(TeamID, this);
    }
}
