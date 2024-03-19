// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/HitEffect/GEHitEffect.h"
#include "GEHitEffect_Sound.generated.h"

class USoundCue;

/**
 *
 */
UCLASS()
class GASEXTENSION_API UGEHitEffect_Sound : public UGEHitEffect
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
