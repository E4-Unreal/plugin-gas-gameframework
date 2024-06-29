// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFExplosiveProjectile.h"
#include "GGFGrenade.generated.h"

/*
 * 수류탄
 */
UCLASS()
class GGFSHOOTERCORE_API AGGFGrenade : public AGGFExplosiveProjectile
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bShouldBounce = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (EditConditionHides, EditCondition = "bShouldBounce"))
    float ExplosionTime = 4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (EditConditionHides, EditCondition = "bShouldBounce"))
    float BounceThreshold = 2;

public:
    AGGFGrenade();

    /* Actor */

    virtual void PostInitializeComponents() override;

protected:
    UFUNCTION(BlueprintNativeEvent, Category = "Event")
    void OnProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);
};
