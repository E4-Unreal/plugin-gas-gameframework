// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFGameMode.h"

#include "Logging.h"
#include "GGFGameState.h"
#include "GGFPlayerController.h"
#include "GGFPlayerState.h"
#include "GameFramework/GameState.h"

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
            }
        }
    }
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
    TArray<APlayerController*> TeamPlayerControllers;
    for(auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        auto OtherPlayerController = It->Get();

        // 자기 자신 무시
        if(OtherPlayerController == PlayerController) continue;

        // 관전자 무시
        if(OtherPlayerController->PlayerState->IsSpectator()) continue;

        // 보유 폰이 없는 경우 무시
        if(OtherPlayerController->GetPawn() == nullptr) continue;

        // 동일한 팀인지 확인
        if(OtherPlayerController->Implements<UGGFTeamInterface>())
        {
            if(IGGFTeamInterface::Execute_GetTeamID(OtherPlayerController) == TeamID)
            {
                TeamPlayerControllers.Emplace(OtherPlayerController);
            }
        }
    }

    // 다른 팀 플레이어가 존재하지 않는 경우 무시
    if(TeamPlayerControllers.IsEmpty()) return;

    // 현재 보고 있는 팀 플레이어 인덱스 확인
    int32 MemberIndex = -1;
    for (int32 Index = 0; Index < TeamPlayerControllers.Num(); ++Index)
    {
        if(PlayerController->GetViewTarget() == TeamPlayerControllers[Index])
        {
            MemberIndex = Index;
            break;
        }
    }

    // 다음으로 볼 팀 플레이어 인덱스 계산
    int32 NextMemberIndex = (MemberIndex + 1) % TeamPlayerControllers.Num();

    // 관전 대상 변경
    PlayerController->SetViewTargetWithBlend(TeamPlayerControllers[NextMemberIndex], 1);

#if WITH_EDITOR
    LOG_ACTOR_DETAIL(Log, TEXT("%s SetViewTarget To %s"), *PlayerController->GetName(), *TeamPlayerControllers[NextMemberIndex]->GetName())
#endif
}
