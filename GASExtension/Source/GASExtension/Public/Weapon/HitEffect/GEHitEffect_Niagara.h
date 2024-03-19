// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEHitEffect.h"
#include "GEHitEffect_Niagara.generated.h"

class UNiagaraSystem;

/**
 *
 */
UCLASS()
class GASEXTENSION_API UGEHitEffect_Niagara : public UGEHitEffect
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    UNiagaraSystem* Niagara;

    UPROPERTY(EditDefaultsOnly)
    FVector Scale = FVector::One();

public:
    virtual void SpawnHitEffect(const FHitResult& HitResult) const override;
};
