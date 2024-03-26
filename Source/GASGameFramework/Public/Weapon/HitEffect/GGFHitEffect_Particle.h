// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFHitEffect.h"
#include "GGFHitEffect_Particle.generated.h"

/**
 *
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGGFHitEffect_Particle : public UGGFHitEffect
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    UParticleSystem* ParticleSystem;

    UPROPERTY(EditDefaultsOnly)
    FVector Scale = FVector::One();

public:
    virtual void SpawnHitEffect(const FHitResult& HitResult) const override;
};
