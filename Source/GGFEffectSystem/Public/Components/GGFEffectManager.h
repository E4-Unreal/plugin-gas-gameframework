// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GGFActorComponent.h"
#include "GGFEffectManager.generated.h"

class UGGFEffectDefinition;

UCLASS(meta=(BlueprintSpawnableComponent))
class GGFEFFECTSYSTEM_API UGGFEffectManager : public UGGFActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bUseInstance = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (EditConditionHides, EditCondition = "!bUseInstance"))
    TObjectPtr<UGGFEffectDefinition> EffectDefinition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Instanced, meta = (EditConditionHides, EditCondition = "bUseInstance"))
    TObjectPtr<UGGFEffectDefinition> InstancedEffectDefinition;

public:
    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void PlayEffectsAtActor(AActor* Actor, bool bAttach = false);

    UFUNCTION(BlueprintCallable)
    virtual void PlayEffectsAtSocket(UPrimitiveComponent* ComponentToAttach, FName SocketName = NAME_None);

    UFUNCTION(BlueprintCallable)
    virtual void PlayEffectsByHitResult(const FHitResult& HitResult, bool bAttach = false);

    UFUNCTION(BlueprintPure)
    FORCEINLINE UGGFEffectDefinition* GetEffectDefinition() const { return bUseInstance ? InstancedEffectDefinition : EffectDefinition; }
};
