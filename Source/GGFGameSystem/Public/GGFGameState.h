// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GGFGameState.generated.h"

/**
 * 팀 정보
 */
USTRUCT(BlueprintType)
struct FGGFTeamInfo
{
    GENERATED_BODY()

    // 팀 ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    uint8 TeamID = 255;

    // 팀에 들어온 순서대로 멤버 ID가 설정됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    uint8 MemberID = 255;

    /* 생성자 */

    FGGFTeamInfo()
    {

    }

    FGGFTeamInfo(uint8 NewTeamID, uint8 NewMemberID)
    {
        TeamID = NewTeamID;
        MemberID = NewMemberID;
    }

    /* 연산자 오버로딩 */

    bool operator ==(const FGGFTeamInfo& Other) const
    {
        return TeamID == Other.TeamID && MemberID == Other.MemberID;
    }
};

/**
 * 팀 슬롯
 */
USTRUCT(BlueprintType)
struct FGGFTeamSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGGFTeamInfo TeamInfo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<APlayerState> PlayerState;

    /* 연산자 오버로딩 */

    // For TArray::Sort
    bool operator >(const FGGFTeamSlot& Other) const
    {
        if(TeamInfo.TeamID > Other.TeamInfo.TeamID) return true;

        if(TeamInfo.TeamID == Other.TeamInfo.TeamID && TeamInfo.MemberID > Other.TeamInfo.MemberID) return true;

        return false;
    }

    // For TArray::Sort
    bool operator <(const FGGFTeamSlot& Other) const
    {
        if(TeamInfo.TeamID < Other.TeamInfo.TeamID) return true;

        if(TeamInfo.TeamID == Other.TeamInfo.TeamID && TeamInfo.MemberID < Other.TeamInfo.MemberID) return true;

        return false;
    }

    // For TArray::Remove
    bool operator ==(const FGGFTeamSlot& Other) const
    {
        return TeamInfo == Other.TeamInfo && PlayerState == Other.PlayerState;
    }

    // For TArray::FindByKey
    bool operator ==(const FGGFTeamInfo& OtherTeamInfo) const
    {
        return TeamInfo == OtherTeamInfo;
    }

    // For TArray::FindByKey
    bool operator ==(const APlayerState* OtherPlayerState) const
    {
        return PlayerState == OtherPlayerState;
    }
};

/**
 * 동일한 팀 플레이어 목록
 */
USTRUCT(BlueprintType)
struct FGGFTeamPlayerList
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FGGFTeamSlot> Slots;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTeamSlotsUpdatedSignature);

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
    FTeamSlotsUpdatedSignature OnTeamSlotsUpdated;

protected:
    // 팀 슬롯 목록
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, ReplicatedUsing = OnRep_TeamSlots)
    TArray<FGGFTeamSlot> TeamSlots;

    // TMap<TeamID, TArray<APlayerState*>>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<uint8, FGGFTeamPlayerList> TeamMap;

    // TMap<APlayerState*, TeamInfo>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<TObjectPtr<APlayerState>, FGGFTeamInfo> PlayerMap;

public:
    /* Actor */

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    /* API */

    // 팀에 플레이어 추가
    UFUNCTION(BlueprintCallable, Category = "ServerOnly")
    virtual void AddPlayerToTeam(uint8 InTeamID, APlayerState* NewPlayerState);

    // 팀으로부터 플레이어 제거
    UFUNCTION(BlueprintCallable, Category = "ServerOnly")
    virtual void RemovePlayerFromTeam(APlayerState* NewPlayerState);

    // 팀 슬롯 리셋
    UFUNCTION(BlueprintCallable, Category = "ServerOnly")
    virtual void ResetTeamSlots();

    // 팀 ID에 대응하는 모든 플레이어 목록 가져오기
    UFUNCTION(BlueprintPure)
    virtual TArray<FGGFTeamSlot> GetTeamSlotsByTeamID(uint8 InTeamID) const;

    // 동일한 팀 플레이어 가져오기
    UFUNCTION(BlueprintPure)
    virtual TArray<FGGFTeamSlot> GetTeamSlotsByPlayer(APlayerState* InPlayer) const;

    // 팀 정보 가져오기
    UFUNCTION(BlueprintPure)
    virtual FGGFTeamInfo GetTeamInfo(APlayerState* InPlayer) const;

protected:
    /* 메서드 */

    // 할당 가능한 멤버 ID 가져오기
    UFUNCTION(BlueprintPure)
    virtual uint8 GetNewMemberID(uint8 InTeamID) const;

    // TeamSlots를 바탕으로 TeamMap 리매핑
    UFUNCTION(BlueprintCallable, Category = "ClientOnly")
    virtual void RefreshTeamMap();

    // TeamSlots를 바탕으로 PlayerMap 리매핑
    UFUNCTION(BlueprintCallable, Category = "ClientOnly")
    virtual void RefreshPlayerMap();

    /* 리플리케이션 */

    UFUNCTION()
    virtual void OnRep_TeamSlots();
};
