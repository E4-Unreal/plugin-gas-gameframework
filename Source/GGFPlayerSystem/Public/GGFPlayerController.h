// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/GGFTeamInterface.h"
#include "GGFPlayerController.generated.h"

/**
 * GASGameFramework 플러그인 전용 플레이어 컨트롤러
 */
UCLASS()
class GGFPLAYERSYSTEM_API AGGFPlayerController : public APlayerController, public IGGFTeamInterface
{
    GENERATED_BODY()

public:
    /* GGFTeamInterface */

    virtual uint8 GetTeamID_Implementation() const override;
    virtual void SetTeamID_Implementation(uint8 NewTeamID) override;
};
