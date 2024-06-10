// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDoor.h"
#include "GGFInteractableDoor.generated.h"

class UBoxComponent;
class UGGFInteractableComponent;

/**
 * 상호작용을 통해 문을 열고 닫을 수 있는 문 액터 클래스입니다.
 */
UCLASS()
class GGFGIMMICKSYSTEM_API AGGFInteractableDoor : public AGGFDoor
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetInteractableArea, Category = "Component")
    TObjectPtr<UBoxComponent> InteractableArea;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetInteractableComponent, Category = "Component")
    TObjectPtr<UGGFInteractableComponent> InteractableComponent;

public:
    AGGFInteractableDoor();

    /* Actor */

    virtual void PostInitializeComponents() override;

protected:
    /* 이벤트 */

    UFUNCTION(BlueprintNativeEvent)
    void OnPawnInteract(APawn* OtherPawn);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UBoxComponent* GetInteractableArea() const { return InteractableArea; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFInteractableComponent* GetInteractableComponent() const { return InteractableComponent; }
};
