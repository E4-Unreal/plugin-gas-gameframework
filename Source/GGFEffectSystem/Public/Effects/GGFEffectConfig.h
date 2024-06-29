// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GGFEffectConfig.generated.h"

/**
 * EffectDefinition에서 사용되는 추가 데이터 에셋
 */
UCLASS(Abstract, DefaultToInstanced, EditInlineNew, CollapseCategories)
class GGFEFFECTSYSTEM_API UGGFEffectConfig : public UDataAsset
{
    GENERATED_BODY()

public:
    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void PlayEffectAtActor(AActor* Actor, bool bAttach = false) { }

    UFUNCTION(BlueprintCallable)
    virtual void PlayEffectAtSocket(UPrimitiveComponent* ComponentToAttach, FName SocketName = NAME_None) { }

    UFUNCTION(BlueprintCallable)
    virtual void PlayEffectByHitResult(const FHitResult& HitResult, bool bAttach = false) { }
};
