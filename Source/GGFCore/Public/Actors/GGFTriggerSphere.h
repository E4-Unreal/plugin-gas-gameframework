// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFTriggerBase.h"
#include "Components/SphereComponent.h"
#include "GGFTriggerSphere.generated.h"

class USphereComponent;

/**
 * 구 콜리전 컴포넌트 오버랩 이벤트가 기본 바인딩된 액터 클래스
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
    FORCEINLINE USphereComponent* GetSphereCollision() const { return Cast<USphereComponent>(GetCollision()); }
};
