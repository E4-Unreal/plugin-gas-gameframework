// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFGameMode.h"

#include "Logging.h"
#include "GGFGameState.h"
#include "GGFPlayerController.h"
#include "GGFPlayerState.h"
#include "GameFramework/GameState.h"

const TArray<APlayerController*> FGGFPlayerControllerList::EmptyList;

AGGFGameMode::AGGFGameMode()
{
    GameStateClass = AGGFGameState::StaticClass();
    PlayerControllerClass = AGGFPlayerController::StaticClass();
    PlayerStateClass = AGGFPlayerState::StaticClass();
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
                if(TeamMap.Contains(0))
                {
                    TeamMap[0].List.Emplace(NewPlayer);
                }
                else
                {
                    FGGFPlayerControllerList PlayerList;
                    PlayerList.List.Emplace(NewPlayer);
                    TeamMap.Emplace(0, PlayerList);
                }
            }
        }
    }
}

const TArray<APlayerController*>& AGGFGameMode::GetTeamListByPlayerController(
    APlayerController* PlayerController) const
{
    if(PlayerController->Implements<UGGFTeamInterface>())
    {
        return GetTeamListByTeamID(IGGFTeamInterface::Execute_GetTeamID(PlayerController));
    }

    return FGGFPlayerControllerList::EmptyList;
}

const TArray<APlayerController*>& AGGFGameMode::GetTeamListByTeamID(int32 TeamID) const
{
    return TeamMap.Contains(TeamID) ? TeamMap[TeamID].List : FGGFPlayerControllerList::EmptyList;
}

void AGGFGameMode::SetViewTargetToPreviousPlayer_Implementation(APlayerController* PlayerController)
{
    // 관전 모드 검사
    if(!PlayerController->PlayerState->IsSpectator()) return;

    // 폰 빙의 해제
    PlayerController->UnPossess();

    // 팀 인터페이스 검사
    if(!PlayerController->Implements<UGGFTeamInterface>()) return;
    uint8 TeamID = IGGFTeamInterface::Execute_GetTeamID(PlayerController);

    // 동일한 팀 플레이어 컨트롤러 가져오기
    const auto& TeamList = GetTeamListByTeamID(TeamID);
    TArray<APlayerController*> AvailableTeamList;
    AvailableTeamList.Reserve(TeamList.Num());
    for (auto OtherPlayerController : TeamList)
    {
        // 자기 자신 무시
        if(OtherPlayerController == PlayerController) continue;

        // 관전자 무시
        if(OtherPlayerController->PlayerState->IsSpectator()) continue;

        // 보유 폰이 없는 경우 무시
        if(OtherPlayerController->GetPawn() == nullptr) continue;

        AvailableTeamList.Emplace(OtherPlayerController);
    }

    // 다른 팀 플레이어가 존재하지 않는 경우 무시
    if(AvailableTeamList.IsEmpty()) return;

    // 현재 보고 있는 팀 플레이어 인덱스 확인
    int32 MemberIndex = -1;
    for (int32 Index = 0; Index < AvailableTeamList.Num(); ++Index)
    {
        if(PlayerController->GetViewTarget() == AvailableTeamList[Index])
        {
            MemberIndex = Index;
            break;
        }

        if(auto Pawn = Cast<APawn>(PlayerController->GetViewTarget()))
        {
            if(Pawn->Controller == AvailableTeamList[Index])
            {
                MemberIndex = Index;
                break;
            }
        }
    }

    // 다음으로 볼 팀 플레이어 인덱스 계산
    int32 NextMemberIndex = MemberIndex <= 0 ? AvailableTeamList.Num() - 1 : MemberIndex - 1;

    // 관전 대상 변경
    PlayerController->SetViewTarget(AvailableTeamList[NextMemberIndex]);

#if WITH_EDITOR
    LOG_ACTOR_DETAIL(Log, TEXT("%s SetViewTarget To %s"), *PlayerController->GetName(), *AvailableTeamList[NextMemberIndex]->GetName())
#endif
}

void AGGFGameMode::SetViewTargetToNextPlayer_Implementation(APlayerController* PlayerController)
{
    // 관전 모드 검사
    if(!PlayerController->PlayerState->IsSpectator()) return;

    // 폰 빙의 해제
    PlayerController->UnPossess();

    // 팀 인터페이스 검사
    if(!PlayerController->Implements<UGGFTeamInterface>()) return;
    uint8 TeamID = IGGFTeamInterface::Execute_GetTeamID(PlayerController);

    // 동일한 팀 플레이어 컨트롤러 가져오기
    const auto& TeamList = GetTeamListByTeamID(TeamID);
    TArray<APlayerController*> AvailableTeamList;
    AvailableTeamList.Reserve(TeamList.Num());
    for (auto OtherPlayerController : TeamList)
    {
        // 자기 자신 무시
        if(OtherPlayerController == PlayerController) continue;

        // 관전자 무시
        if(OtherPlayerController->PlayerState->IsSpectator()) continue;

        // 보유 폰이 없는 경우 무시
        if(OtherPlayerController->GetPawn() == nullptr) continue;

        AvailableTeamList.Emplace(OtherPlayerController);
    }

    // 다른 팀 플레이어가 존재하지 않는 경우 무시
    if(AvailableTeamList.IsEmpty()) return;

    // 현재 보고 있는 팀 플레이어 인덱스 확인
    int32 MemberIndex = -1;
    for (int32 Index = 0; Index < AvailableTeamList.Num(); ++Index)
    {
        if(PlayerController->GetViewTarget() == AvailableTeamList[Index])
        {
            MemberIndex = Index;
            break;
        }

        if(auto Pawn = Cast<APawn>(PlayerController->GetViewTarget()))
        {
            if(Pawn->Controller == AvailableTeamList[Index])
            {
                MemberIndex = Index;
                break;
            }
        }
    }

    // 다음으로 볼 팀 플레이어 인덱스 계산
    int32 NextMemberIndex = (MemberIndex + 1) % AvailableTeamList.Num();

    // 관전 대상 변경
    PlayerController->SetViewTarget(AvailableTeamList[NextMemberIndex]);

#if WITH_EDITOR
    LOG_ACTOR_DETAIL(Log, TEXT("%s SetViewTarget To %s"), *PlayerController->GetName(), *AvailableTeamList[NextMemberIndex]->GetName())
#endif
}
