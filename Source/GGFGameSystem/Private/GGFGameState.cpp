// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFGameState.h"

#include "GGFPlayerState.h"

void AGGFGameState::RefreshTeamPlayerList()
{
    // 초기화
    TeamPlayerList.Reset();

    // 팀 플레이어 목록 갱신
    for (auto PlayerState : PlayerArray)
    {
        if(auto CastedPlayerState = Cast<AGGFPlayerState>(PlayerState))
        {
            AddTeamPlayer(CastedPlayerState);
        }
    }

    // 이벤트 호출
    OnTeamPlayerListRefreshed.Broadcast();
}

TArray<APlayerState*> AGGFGameState::GetPlayersByTeamID(uint8 TeamID) const
{
    // 팀이 존재하는 경우
    for (const auto& TeamPlayer : TeamPlayerList)
    {
        if(TeamPlayer.TeamID == TeamID)
        {
            return TeamPlayer.PlayerStates;
        }
    }

    // 팀이 존재하지 않는 경우
    return TArray<APlayerState*>();
}

TArray<APlayerState*> AGGFGameState::GetPlayersByPlayerState(APlayerState* InPlayerState) const
{
    if(auto CastedPlayerState = Cast<AGGFPlayerState>(InPlayerState))
    {
        return GetPlayersByTeamID(CastedPlayerState->GetTeamInfo().TeamID);
    }

    return TArray<APlayerState*>();
}

void AGGFGameState::AddTeamPlayer(AGGFPlayerState* NewPlayerState)
{
    // 입력 유효성 검사
    if(NewPlayerState == nullptr) return;

    // 팀 ID
    const uint8 TeamID = NewPlayerState->GetTeamInfo().TeamID;

    // 팀이 이미 존재하는 경우
    for (auto& TeamPlayer : TeamPlayerList)
    {
        if(TeamPlayer.TeamID == TeamID)
        {
            TeamPlayer.PlayerStates.Emplace(NewPlayerState);

            return;
        }
    }

    // 새로운 팀인 경우
    FGGFTeamPlayerContainer NewTeamPlayer;
    NewTeamPlayer.TeamID = TeamID;
    NewTeamPlayer.PlayerStates.Emplace(NewPlayerState);

    TeamPlayerList.Emplace(NewTeamPlayer);
}
