// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFTeamTypes.generated.h"

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

    bool Equals(const FGGFTeamInfo& Other) const
    {
        return TeamID == Other.TeamID && MemberID == Other.MemberID;
    }

    bool operator ==(const FGGFTeamInfo& Other) const
    {
        return Equals(Other);
    }

    friend uint32 GetTypeHash(const FGGFTeamInfo& TeamInfo)
    {
        return FCrc::MemCrc32(&TeamInfo, sizeof(TeamInfo));
    }

    bool operator <(const FGGFTeamInfo& Other) const
    {
        if(TeamID < Other.TeamID) return true;

        if(TeamID == Other.TeamID && MemberID < Other.MemberID) return true;

        return false;
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

    /* 생성자 */

    FGGFTeamSlot()
    {

    }

    FGGFTeamSlot(APlayerState* InPlayerState, const FGGFTeamInfo& InTeamInfo)
    {
        PlayerState = InPlayerState;
        TeamInfo = InTeamInfo;
    }

    /* 연산자 오버로딩 */

    bool operator ==(const FGGFTeamSlot& Other) const
    {
        return TeamInfo == Other.TeamInfo && PlayerState == Other.PlayerState;
    }

    bool operator <(const FGGFTeamSlot& Other) const
    {
        return TeamInfo < Other.TeamInfo;
    }

    bool operator ==(const FGGFTeamInfo& OtherTeamInfo) const
    {
        return TeamInfo == OtherTeamInfo;
    }

    bool operator ==(APlayerState* OtherPlayerState) const
    {
        return PlayerState == OtherPlayerState;
    }
};

/**
 * 팀 슬롯 목록
 */
USTRUCT(BlueprintType)
struct FGGFTeamSlotList
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FGGFTeamSlot> Slots;
};
