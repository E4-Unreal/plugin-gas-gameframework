// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GGFInteractableActor.h"
#include "Interfaces/GGFActivatableInterface.h"
#include "GGFInteractableTrigger.generated.h"

class UGGFActivatableComponent;
class UGGFTriggerComponent;

/**
 * 상호작용 가능한 트리거 전용 액터입니다.
 */
UCLASS()
class GGFGIMMICKSYSTEM_API AGGFInteractableTrigger : public AGGFInteractableActor, public IGGFActivatableInterface
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetTriggerComponent, Category = "Component")
    TObjectPtr<UGGFTriggerComponent> TriggerComponent;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetActivatableComponent, Category = "Component")
    TObjectPtr<UGGFActivatableComponent> ActivatableComponent;

public:
    AGGFInteractableTrigger();

protected:
    /* InteractableActor */

    virtual void OnPawnInteract_Implementation(APawn* OtherPawn) override;

    /* ActivationInterface */

    virtual bool TryActivate_Implementation(AActor* InCauser, AActor* InInstigator) override;
    virtual bool TryDeactivate_Implementation(AActor* InCauser, AActor* InInstigator) override;

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFTriggerComponent* GetTriggerComponent() const { return TriggerComponent; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFActivatableComponent* GetActivatableComponent() const { return ActivatableComponent; }
};
