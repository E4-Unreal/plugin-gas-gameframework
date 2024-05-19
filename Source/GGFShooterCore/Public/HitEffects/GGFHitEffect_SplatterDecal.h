// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFHitEffect_Decal.h"
#include "GGFHitEffect_SplatterDecal.generated.h"

/**
 * 피격 대상이 관통되면서 뒤에 있는 오브젝트에 부착되는 데칼입니다.
 */
UCLASS()
class GGFSHOOTERCORE_API UGGFHitEffect_SplatterDecal : public UGGFHitEffect_Decal
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    float Distance = 300.f;

public:
    virtual void SpawnHitEffect(const FHitResult& HitResult) const override;
};
