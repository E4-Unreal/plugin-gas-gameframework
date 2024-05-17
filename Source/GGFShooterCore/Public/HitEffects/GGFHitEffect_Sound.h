// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFHitEffect.h"
#include "GGFHitEffect_Sound.generated.h"

class USoundCue;

/**
 *
 */
UCLASS()
class GGFSHOOTERCORE_API UGGFHitEffect_Sound : public UGGFHitEffect
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    USoundCue* Sound;

    UPROPERTY(EditDefaultsOnly)
    float VolumeMultiplier = 1;

    UPROPERTY(EditDefaultsOnly)
    float PitchMultiplier = 1;

    UPROPERTY(EditDefaultsOnly)
    float StartTime = 0;

public:
    virtual void SpawnHitEffect(const FHitResult& HitResult) const override;
};
