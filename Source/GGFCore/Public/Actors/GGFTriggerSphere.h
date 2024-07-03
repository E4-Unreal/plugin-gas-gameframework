// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFTriggerBase.h"
#include "Components/SphereComponent.h"
#include "GGFTriggerSphere.generated.h"

class USphereComponent;

/**
 * 기본 트리거 액터 - 구
 */
UCLASS()
class GGFCORE_API AGGFTriggerSphere : public AGGFTriggerBase
{
    GENERATED_BODY()

public:
    AGGFTriggerSphere(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
    /* Getter */

    UFUNCTION(BlueprintPure)
    FORCEINLINE USphereComponent* GetSphereCollision() const { return Cast<USphereComponent>(GetCollisionComponent()); }
};
