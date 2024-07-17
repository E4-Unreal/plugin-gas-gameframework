// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFPlayerState.h"

#include "Logging.h"
#include "AbilitySystemGlobals.h"
#include "GGFGameState.h"
#include "Net/UnrealNetwork.h"

void AGGFPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, TeamInfo)
}

void AGGFPlayerState::BeginPlay()
{
    Super::BeginPlay();

    if(auto GameState = GetWorld()->GetGameState<AGGFGameState>())
    {
        GameState->SetPlayerTeamInfo(this, TeamInfo);
    }
}

UAbilitySystemComponent* AGGFPlayerState::GetAbilitySystemComponent() const
{
    return UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetPawn());
}

FGenericTeamId AGGFPlayerState::GetGenericTeamId() const
{
    return TeamInfo.TeamID;
}

void AGGFPlayerState::SetGenericTeamId(const FGenericTeamId& TeamID)
{
    if(auto GameState = GetWorld()->GetGameState<AGGFGameState>())
    {
        GameState->SetPlayerTeam(this, TeamID);
    }
}

void AGGFPlayerState::SetTeamInfo(const FGGFTeamInfo& NewTeamInfo)
{
    TeamInfo = NewTeamInfo;
}

void AGGFPlayerState::OnRep_TeamInfo(const FGGFTeamInfo& OldTeamInfo)
{
#if WITH_EDITOR
    LOG_ACTOR_DETAIL(Log, TEXT("OldTeamInfo: (%d, %d), NewTeamInfo: (%d, %d)"), OldTeamInfo.TeamID, OldTeamInfo.MemberID, TeamInfo.TeamID, TeamInfo.MemberID)
#endif

    if(auto GameState = GetWorld()->GetGameState<AGGFGameState>())
    {
        GameState->SetPlayerTeamInfo(this, TeamInfo);
    }
}
