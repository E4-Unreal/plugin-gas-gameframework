// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFTriggerSphere.h"
#include "GGFEffectSphere.generated.h"

class UGGFEffectAreaComponent;

UCLASS()
class GGFCORE_API AGGFEffectSphere : public AGGFTriggerSphere
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetEffectAreaComponent, Category = "Component")
    TObjectPtr<UGGFEffectAreaComponent> EffectAreaComponent;

public:
    AGGFEffectSphere(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void PostInitializeComponents() override;

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFEffectAreaComponent* GetEffectAreaComponent() const { return EffectAreaComponent; }
};
