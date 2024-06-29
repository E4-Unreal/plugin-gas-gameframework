// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGA_SpawnActor.h"
#include "GGFGA_SpawnTurret.generated.h"

/**
 * 터렛 소환 스킬
 */
UCLASS()
class GGFSKILLSYSTEM_API UGGFGA_SpawnTurret : public UGGFGA_SpawnActor
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName HandSocketName = "hand_l";

protected:
    /* GGFGA_SpawnActor */

    virtual void SpawnActor() override;
};
