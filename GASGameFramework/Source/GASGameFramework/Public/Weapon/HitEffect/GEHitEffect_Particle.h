// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEHitEffect.h"
#include "GEHitEffect_Particle.generated.h"

/**
 *
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGEHitEffect_Particle : public UGEHitEffect
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    UParticleSystem* ParticleSystem;

    UPROPERTY(EditDefaultsOnly)
    FVector Scale = FVector::One();

public:
    virtual void SpawnHitEffect(const FHitResult& HitResult) const override;
};
