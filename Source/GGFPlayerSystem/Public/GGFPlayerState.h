// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerState.h"
#include "GGFPlayerState.generated.h"

/**
 * 팀 정보
 */
USTRUCT(BlueprintType)
struct FGGFTeamInfo
{
    GENERATED_BODY()

    // 팀 ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    uint8 TeamID = FGenericTeamId::NoTeam;

    // 팀에 들어온 순서대로 멤버 ID가 설정됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    uint8 MemberID;
};

/**
 * GASGameFramework 플러그인 전용 플레이어 스테이트
 */
UCLASS()
class GGFPLAYERSYSTEM_API AGGFPlayerState : public APlayerState, public IGenericTeamAgentInterface
{
    GENERATED_BODY()

    // 호스트 여부
    UPROPERTY(VisibleAnywhere, BlueprintSetter = SetHost, Category = "State", Transient, ReplicatedUsing = OnRep_Host)
    bool bHost = false;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetTeamInfo, BlueprintSetter = SetTeamInfo, Category = "State", Transient, ReplicatedUsing = OnRep_TeamInfo)
    FGGFTeamInfo TeamInfo;

public:
    /* Actor */

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    /* GenericTeamAgentInterface */

    virtual FORCEINLINE FGenericTeamId GetGenericTeamId() const override { return TeamInfo.TeamID; }
    virtual FORCEINLINE void SetGenericTeamId(const FGenericTeamId& TeamID) override { TeamInfo.TeamID = TeamID; }

    /* API */

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsHost() const { return bHost; }

    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FGGFTeamInfo& GetTeamInfo() const { return TeamInfo; }

    /* Setter */

    UFUNCTION(BlueprintSetter)
    void SetHost(bool bNewHost);

    UFUNCTION(BlueprintSetter)
    void SetTeamInfo(const FGGFTeamInfo& NewTeamInfo);

protected:
    /* PlayerState */

    virtual void CopyProperties(APlayerState* PlayerState) override;

    /* 리플리케이트 */

    UFUNCTION()
    virtual void OnRep_Host();

    UFUNCTION()
    virtual void OnRep_TeamInfo(const FGGFTeamInfo& OldTeamInfo);
};
