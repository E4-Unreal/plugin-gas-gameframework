// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GGFGameState.generated.h"

/**
 * 팀 플레이어
 */
USTRUCT(BlueprintType)
struct FGGFTeamPlayerContainer
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    uint8 TeamID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TObjectPtr<APlayerState>> PlayerStates;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTeamPlayerListRefreshedSignature);

class AGGFPlayerState;

/**
 * GASGameFramework 플러그인 전용 게임 스테이트
 */
UCLASS()
class GGFGAMESYSTEM_API AGGFGameState : public AGameState
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FTeamPlayerListRefreshedSignature OnTeamPlayerListRefreshed;

protected:
    // 팀 플레이어 목록
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<FGGFTeamPlayerContainer> TeamPlayerList;

public:
    /* API */

    // 팀 플레이어 목록 갱신
    UFUNCTION(BlueprintCallable)
    virtual void RefreshTeamPlayerList();

    // 팀 플레이어 가져오기
    UFUNCTION(BlueprintCallable)
    TArray<APlayerState*> GetPlayersByTeamID(uint8 TeamID) const;

    // 팀 플레이어 가져오기
    UFUNCTION(BlueprintCallable)
    TArray<APlayerState*> GetPlayersByPlayerState(APlayerState* InPlayerState) const;

protected:
    // 팀 플레어 목록에 새로운 플레이어 스테이트 추가
    virtual void AddTeamPlayer(AGGFPlayerState* NewPlayerState);
};
