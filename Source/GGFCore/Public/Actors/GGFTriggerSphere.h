// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGFTriggerSphere.generated.h"

class USphereComponent;

/**
 * 기본 트리거 액터 - 구
 */
UCLASS()
class GGFCORE_API AGGFTriggerSphere : public AActor
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetTriggerSphere, Category = "Component")
    TObjectPtr<USphereComponent> TriggerSphere;

public:
    AGGFTriggerSphere(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void PostInitializeComponents() override;

protected:
    /* 이벤트 */

    UFUNCTION(BlueprintNativeEvent)
    void OnTriggerSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintNativeEvent)
    void OnTriggerSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USphereComponent* GetTriggerSphere() const { return TriggerSphere; }
};
