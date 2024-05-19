// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFHitEffect.h"
#include "GGFHitEffect_Decal.generated.h"

/**
 *
 */
UCLASS()
class GGFSHOOTERCORE_API UGGFHitEffect_Decal : public UGGFHitEffect
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly)
    UMaterialInterface* DecalMaterial;

    UPROPERTY(EditDefaultsOnly)
    float MaxSize = 100.f;

    UPROPERTY(EditDefaultsOnly)
    float MinSize = 10.f;

    UPROPERTY(EditDefaultsOnly)
    float Depth = 10.f;

public:
    virtual void SpawnHitEffect(const FHitResult& HitResult) const override;
};
