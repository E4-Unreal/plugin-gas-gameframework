// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFGameState.h"

#include "Logging.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"

void AGGFGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, TeamSlots)
}

void AGGFGameState::AddPlayerToTeam(uint8 InTeamID, APlayerState* NewPlayerState)
{
    // 서버에서만 호출 가능
    if(!HasAuthority())
    {
#if WITH_EDITOR
        LOG_ACTOR_DETAIL(Warning, TEXT("서버에서만 호출이 가능합니다."))
#endif
        return;
    }

    // 입력 유효성 검사
    ensure(NewPlayerState);

    // 중복 호출 방지
    if(PlayerMap.Contains(NewPlayerState))
    {
#if WITH_EDITOR
        LOG_ACTOR_DETAIL(Warning, TEXT("이미 등록된 플레이어입니다. (%s)"), *NewPlayerState->GetName())
#endif
        return;
    }

    // TeamInfo 설정
    const FGGFTeamInfo NewTeamInfo(InTeamID, GetNewMemberID(InTeamID));

    // 팀 슬롯 추가 및 정렬
    TeamSlots.Emplace(NewTeamInfo, NewPlayerState);
    TeamSlots.Sort();

    // 팀 매핑 정보 추가 및 정렬
    if(TeamMap.Contains(InTeamID))
    {
        TeamMap[InTeamID].Slots.Emplace(NewTeamInfo, NewPlayerState);
        TeamMap[InTeamID].Slots.Sort();
    }
    else
    {
        FGGFTeamPlayerList NewTeamPlayerList;
        NewTeamPlayerList.Slots.Emplace(NewTeamInfo, NewPlayerState);
        TeamMap.Emplace(InTeamID, NewTeamPlayerList);
    }

    // 플레이어 매핑 정보 추가
    PlayerMap.Emplace(NewPlayerState, NewTeamInfo);
}

void AGGFGameState::RemovePlayerFromTeam(APlayerState* NewPlayerState)
{
    // 서버에서만 호출 가능
    if(!HasAuthority())
    {
#if WITH_EDITOR
        LOG_ACTOR_DETAIL(Warning, TEXT("서버에서만 호출이 가능합니다."))
#endif
        return;
    }

    // 입력 유효성 검사
    ensure(NewPlayerState);

    // 플레이어 등록 여부 확인
    if(!PlayerMap.Contains(NewPlayerState))
    {
#if WITH_EDITOR
        LOG_ACTOR_DETAIL(Warning, TEXT("등록되지 않은 플레이어입니다. (%s)"), *NewPlayerState->GetName())
#endif
        return;
    }

    // 지역 변수 선언
    FGGFTeamSlot LocalTeamSlot;
    LocalTeamSlot.PlayerState = NewPlayerState;
    LocalTeamSlot.TeamInfo = PlayerMap[NewPlayerState];

    uint8 LocalTeamID = LocalTeamSlot.TeamInfo.TeamID;

    // 팀 슬롯 제거 (정렬 유지)
    TeamSlots.Remove(LocalTeamSlot);

    // 팀 매핑 정보 제거 (정렬 유지)
    TeamMap[LocalTeamID].Slots.Remove(LocalTeamSlot);
    if(TeamMap[LocalTeamID].Slots.IsEmpty()) TeamMap.Remove(LocalTeamID);

    // 플레이어 매핑 정보 제거
    PlayerMap.Remove(NewPlayerState);
}

void AGGFGameState::ResetTeamSlots()
{
    // 서버에서만 호출 가능
    if(!HasAuthority())
    {
#if WITH_EDITOR
        LOG_ACTOR_DETAIL(Warning, TEXT("서버에서만 호출이 가능합니다."))
#endif
        return;
    }

    // 팀 슬롯 리셋
    TeamSlots.Reset();

    // 팀 매핑 정보 리셋
    TeamMap.Reset();

    // 플레이어 매핑 정보 리셋
    PlayerMap.Reset();
}

TArray<FGGFTeamSlot> AGGFGameState::GetTeamSlotsByTeamID(uint8 InTeamID) const
{
    return TeamMap.Contains(InTeamID) ? TeamMap[InTeamID].Slots : TArray<FGGFTeamSlot>();
}

TArray<FGGFTeamSlot> AGGFGameState::GetTeamSlotsByPlayer(APlayerState* InPlayer) const
{
    return PlayerMap.Contains(InPlayer) ? GetTeamSlotsByTeamID(PlayerMap[InPlayer].TeamID) : TArray<FGGFTeamSlot>();
}

FGGFTeamInfo AGGFGameState::GetTeamInfo(APlayerState* InPlayer) const
{
    return PlayerMap.Contains(InPlayer) ? PlayerMap[InPlayer] : FGGFTeamInfo();
}

uint8 AGGFGameState::GetNewMemberID(uint8 InTeamID) const
{
    uint8 NewMemberID = 0;

    if(TeamMap.Contains(InTeamID))
    {
        for (const auto& SortedSlot : TeamMap[InTeamID].Slots)
        {
            if(SortedSlot.TeamInfo.MemberID != NewMemberID) break;

            ++NewMemberID;
        }
    }

    return NewMemberID;
}

void AGGFGameState::RefreshTeamMap()
{
    // 클라이언트에서만 호출 가능
    if(HasAuthority())
    {
#if WITH_EDITOR
        LOG_ACTOR_DETAIL(Warning, TEXT("클라이언트에서만 호출이 가능합니다."))
#endif
        return;
    }

    // 초기화
    TeamMap.Reset();

    // TeamSlots 분석
    for (const auto& SortedTeamSlot : TeamSlots)
    {
        const uint8 NewTeamID = SortedTeamSlot.TeamInfo.TeamID;

        if(TeamMap.Contains(NewTeamID))
        {
            TeamMap[NewTeamID].Slots.Emplace(SortedTeamSlot);
        }
        else
        {
            FGGFTeamPlayerList NewTeamPlayerList;
            NewTeamPlayerList.Slots.Emplace(SortedTeamSlot);
            TeamMap.Emplace(NewTeamID, NewTeamPlayerList);
        }
    }
}

void AGGFGameState::RefreshPlayerMap()
{
    // 클라이언트에서만 호출 가능
    if(HasAuthority())
    {
#if WITH_EDITOR
        LOG_ACTOR_DETAIL(Warning, TEXT("클라이언트에서만 호출이 가능합니다."))
#endif
        return;
    }

    // 초기화
    PlayerMap.Reset();

    // TeamSlots 분석
    for (const auto& SortedTeamSlot : TeamSlots)
    {
        PlayerMap.Emplace(SortedTeamSlot.PlayerState, SortedTeamSlot.TeamInfo);
    }
}

void AGGFGameState::OnRep_TeamSlots()
{
    RefreshTeamMap();
    RefreshPlayerMap();

    OnTeamSlotsUpdated.Broadcast();
}
