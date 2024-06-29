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

    /* API */

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    uint8 GetTeamID() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetTeamID(uint8 NewTeamID);

protected:
    UFUNCTION()
    virtual void OnRep_TeamID(uint8 OldTeamID);
};
