// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEHitEffect.h"
#include "GEHitEffect_Decal.generated.h"

/**
 *
 */
UCLASS()
class GASEXTENSION_API UGEHitEffect_Decal : public UGEHitEffect
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
