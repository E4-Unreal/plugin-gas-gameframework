// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/GGFTeamInterface.h"
#include "GGFPlayerState.generated.h"

/**
 * GASGameFramework 플러그인 전용 플레이어 스테이트
 */
UCLASS()
class GGFPLAYERSYSTEM_API AGGFPlayerState : public APlayerState, public IGGFTeamInterface
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_TeamID)
    uint8 TeamID = NoTeam;

public:
    /* Actor */

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    /* GGFTeamInterface */

    virtual FORCEINLINE uint8 GetTeamID_Implementation() const override { return TeamID; }
    virtual FORCEINLINE void SetTeamID_Implementation(uint8 NewTeamID) override;

protected:
    UFUNCTION()
    virtual void OnRep_TeamID(uint8 OldTeamID);
};
