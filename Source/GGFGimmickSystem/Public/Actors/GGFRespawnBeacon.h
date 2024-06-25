// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GGFInteractableActor.h"
#include "GGFRespawnBeacon.generated.h"

class UArrowComponent;

/**
 * 죽은 플레이어를 모두 살리는 상호작용 오브젝트입니다.
 */
UCLASS()
class GGFGIMMICKSYSTEM_API AGGFRespawnBeacon : public AGGFInteractableActor
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetRespawnPlaceholder, Category = "Component")
    TObjectPtr<UArrowComponent> RespawnPlaceholder;

public:
    AGGFRespawnBeacon();

protected:
    /* InteractableActor */

    virtual void OnPawnInteract_Implementation(APawn* OtherPawn) override;

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UArrowComponent* GetRespawnPlaceholder() const { return RespawnPlaceholder; }
};
