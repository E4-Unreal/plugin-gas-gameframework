// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GGFEffectDefinition.generated.h"

class UGGFEffectConfig;

/**
 *
 */
UCLASS(BlueprintType, EditInlineNew, CollapseCategories)
class GGFEFFECTSYSTEM_API UGGFEffectDefinition : public UDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere)
    TArray<TObjectPtr<UGGFEffectConfig>> EffectConfigs;

public:
    /* API */

    UFUNCTION(BlueprintCallable)
    FORCEINLINE void Init(const TArray<UGGFEffectConfig*> NewEffectConfigs) { EffectConfigs = NewEffectConfigs; }

    UFUNCTION(BlueprintCallable)
    virtual void PlayEffectsAtActor(AActor* Actor, bool bAttach = false);

    UFUNCTION(BlueprintCallable)
    virtual void PlayEffectsAtSocket(UPrimitiveComponent* ComponentToAttach, FName SocketName = NAME_None);

    UFUNCTION(BlueprintCallable)
    virtual void PlayEffectsByHitResult(const FHitResult& HitResult, bool bAttach = false);
};
