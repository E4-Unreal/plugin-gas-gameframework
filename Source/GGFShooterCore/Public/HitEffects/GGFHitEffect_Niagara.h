// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFHitEffect.h"
#include "GGFHitEffect_Niagara.generated.h"

class UNiagaraSystem;

/**
 *
 */
UCLASS()
class GGFSHOOTERCORE_API UGGFHitEffect_Niagara : public UGGFHitEffect
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    UNiagaraSystem* Niagara;

    UPROPERTY(EditDefaultsOnly)
    FVector Scale = FVector::One();

public:
    virtual void SpawnHitEffect(const FHitResult& HitResult) const override;
};
