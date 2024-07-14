// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFGameState.h"

#include "GGFPlayerState.h"
#include "Logging.h"

void AGGFGameState::SetPlayerTeam(APlayerState* Player, uint8 NewTeamID)
{
    SetPlayerTeamInfo(Player, FGGFTeamInfo(NewTeamID, GetNewMemberID(NewTeamID)));
}

void AGGFGameState::SetPlayerTeamInfo(APlayerState* Player, const FGGFTeamInfo& NewTeamInfo)
{
    ensure(Player);

    // 중복 호출 방지
    if(PlayerMap.Contains(Player) && PlayerMap[Player].TeamID == NewTeamInfo.TeamID)
    {
#if WITH_EDITOR
        LOG_ACTOR_DETAIL(Warning, TEXT("이미 팀에 속해있는 플레이어입니다. (%d)"), NewTeamInfo.TeamID)
#endif

        return;
    }

    // 지역 변수 선언
    FGGFTeamInfo OldTeamInfo = PlayerMap.Contains(Player) ? PlayerMap[Player] : FGGFTeamInfo();

    // 기존 팀 정보 제거 후 새로운 팀 정보 추가
    RemovePlayerFromTeam(Player);
    AddPlayerToTeam(Player, NewTeamInfo);

    // PlayerState에 팀 정보 설정
    if(auto CastedPlayerState = Cast<AGGFPlayerState>(Player))
    {
        CastedPlayerState->SetTeamInfo(NewTeamInfo);
    }

    // 이벤트 호출
    OnTeamInfoUpdated.Broadcast(Player, OldTeamInfo, NewTeamInfo);

#if WITH_EDITOR
    LOG_ACTOR_DETAIL(Log, TEXT("%s: (%d, %d) > (%d, %d)"), *Player->GetName(), OldTeamInfo.TeamID, OldTeamInfo.MemberID, NewTeamInfo.TeamID, NewTeamInfo.MemberID);
#endif
}

TArray<FGGFTeamSlot> AGGFGameState::GetTeamSlotsByTeamID(uint8 TeamID)
{
    return TeamMap.Contains(TeamID) ? TeamMap[TeamID].Slots : TArray<FGGFTeamSlot>();
}

TArray<FGGFTeamSlot> AGGFGameState::GetTeamSlotsByPlayer(APlayerState* Player)
{
    return PlayerMap.Contains(Player) ? GetTeamSlotsByTeamID(PlayerMap[Player].TeamID) : TArray<FGGFTeamSlot>();
}

void AGGFGameState::AddPlayerToTeam(APlayerState* Player, const FGGFTeamInfo& NewTeamInfo)
{
    // TeamMap 등록
    if(TeamMap.Contains(NewTeamInfo.TeamID))
    {
        TeamMap[NewTeamInfo.TeamID].Slots.Emplace(Player, NewTeamInfo);
        TeamMap[NewTeamInfo.TeamID].Slots.Sort();
    }
    else
    {
        FGGFTeamSlotList NewTeamSlotList;
        NewTeamSlotList.Slots.Emplace(Player, NewTeamInfo);

        TeamMap.Emplace(NewTeamInfo.TeamID, NewTeamSlotList);
    }

    // PlayerMap 등록
    PlayerMap.Emplace(Player, NewTeamInfo);
}

void AGGFGameState::RemovePlayerFromTeam(APlayerState* Player)
{
    // 등록되지 않은 경우
    if(!PlayerMap.Contains(Player)) return;

    // 지역 변수 선언
    const FGGFTeamInfo OldTeamInfo = PlayerMap[Player];

    // TeamMap에서 제거
    auto& TeamSlots = TeamMap[OldTeamInfo.TeamID].Slots;
    if(auto TeamSlotPtr = TeamSlots.FindByKey(Player)) TeamSlots.Remove(*TeamSlotPtr);
    if(TeamSlots.IsEmpty()) TeamMap.Remove(OldTeamInfo.TeamID);

    // PlayerMap에서 제거
    PlayerMap.Remove(Player);
}

uint8 AGGFGameState::GetNewMemberID(uint8 InTeamID) const
{
    uint8 NewMemberID = 0;

    if(TeamMap.Contains(InTeamID))
    {
        for (const auto& TeamSlot : TeamMap[InTeamID].Slots)
        {
            if(TeamSlot.TeamInfo.MemberID == NewMemberID)
            {
                ++NewMemberID;
            }
            else
            {
                break;
            }
        }
    }

    return NewMemberID;
}
