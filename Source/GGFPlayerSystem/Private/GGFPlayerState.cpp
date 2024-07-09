// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFPlayerState.h"

#include "GGFGameState.h"
#include "Logging.h"
#include "Net/UnrealNetwork.h"

void AGGFPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, bHost)
    DOREPLIFETIME(ThisClass, TeamInfo)
}

void AGGFPlayerState::CopyProperties(APlayerState* PlayerState)
{
    Super::CopyProperties(PlayerState);

    if(auto CastedPlayerState = Cast<AGGFPlayerState>(PlayerState))
    {
        CastedPlayerState->SetTeamInfo(TeamInfo);
    }
}

void AGGFPlayerState::SetHost(bool bNewHost)
{
#if WITH_EDITOR
    if(bNewHost)
    {
        LOG_ACTOR_DETAIL(Log, TEXT("호스트로 지정되었습니다."))
    }
    else
    {
        LOG_ACTOR_DETAIL(Log, TEXT("호스트 지정이 해제되었습니다."))
    }
#endif

    bHost = bNewHost;
}

void AGGFPlayerState::OnRep_Host()
{
#if WITH_EDITOR
    if(bHost)
    {
        LOG_ACTOR_DETAIL(Log, TEXT("호스트로 지정되었습니다."))
    }
    else
    {
        LOG_ACTOR_DETAIL(Log, TEXT("호스트 지정이 해제되었습니다."))
    }
#endif
}

void AGGFPlayerState::SetTeamInfo(const FGGFTeamInfo& NewTeamInfo)
{
#if WITH_EDITOR
    LOG_ACTOR_DETAIL(Log, TEXT("OldTeamInfo: (%d, %d), NewTeamInfo: (%d, %d)"), TeamInfo.TeamID, TeamInfo.MemberID, NewTeamInfo.TeamID, NewTeamInfo.MemberID)
#endif

    TeamInfo = NewTeamInfo;
}

void AGGFPlayerState::OnRep_TeamInfo(const FGGFTeamInfo& OldTeamInfo)
{
#if WITH_EDITOR
    LOG_ACTOR_DETAIL(Log, TEXT("OldTeamInfo: (%d, %d), NewTeamInfo: (%d, %d)"), OldTeamInfo.TeamID, OldTeamInfo.MemberID, TeamInfo.TeamID, TeamInfo.MemberID)
#endif

    // 팀 플레이어 목록 갱신
    if(auto GameState = GetWorld()->GetGameState<AGGFGameState>())
    {
        GameState->RefreshTeamPlayerList();
    }
}
