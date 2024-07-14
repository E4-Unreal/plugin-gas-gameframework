// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Types/GGFTeamTypes.h"
#include "GGFGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTeamInfoUpdatedSignature, APlayerState*, Player, const FGGFTeamInfo&, OldTeamInfo, const FGGFTeamInfo&, NewTeamInfo);

class AGGFPlayerState;

/**
 * GASGameFramework 플러그인 전용 게임 스테이트
 */
UCLASS()
class GGFGAMESYSTEM_API AGGFGameState : public AGameState
{
    GENERATED_BODY()

public:
    /* 델리게이트 */

    UPROPERTY(BlueprintAssignable)
    FTeamInfoUpdatedSignature OnTeamInfoUpdated;

    // true로 설정된 경우 아군 공격에 데미지를 입습니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bAllowTeamDamage = true;

protected:
    // TMap<TeamID, TArray<TeamSlot>>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<uint8, FGGFTeamSlotList> TeamMap;

    // TMap<Player, TeamInfo>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<TObjectPtr<APlayerState>, FGGFTeamInfo> PlayerMap;

public:
    /* API */

    UFUNCTION()
    virtual void SetPlayerTeam(APlayerState* Player, uint8 NewTeamID);

    UFUNCTION()
    virtual void SetPlayerTeamInfo(APlayerState* Player, const FGGFTeamInfo& NewTeamInfo);

    UFUNCTION()
    FORCEINLINE FGGFTeamInfo GetPlayerTeamInfo(APlayerState* Player) { return PlayerMap.Contains(Player) ? PlayerMap[Player] : FGGFTeamInfo(); }

    UFUNCTION()
    TArray<FGGFTeamSlot> GetTeamSlotsByTeamID(uint8 TeamID);

    UFUNCTION()
    TArray<FGGFTeamSlot> GetTeamSlotsByPlayer(APlayerState* Player);

protected:
    /* 메서드 */

    // 팀에 플레이어 추가
    virtual void AddPlayerToTeam(APlayerState* Player, const FGGFTeamInfo& NewTeamInfo);

    // 팀으로부터 플레이어 제거
    virtual void RemovePlayerFromTeam(APlayerState* Player);

    // 비어있는 멤버 ID 가져오기
    virtual uint8 GetNewMemberID(uint8 InTeamID) const;
};
