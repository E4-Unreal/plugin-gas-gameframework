// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFInteractionSystem/Public/Actors/GGFInteractableActor.h"
#include "GGFPickupEquipment.generated.h"

// TODO ItemSystem 모듈 연동 필요
/**
 * 월드에 스폰 혹은 드랍된 장비 전용 아이템 클래스
 */
UCLASS()
class GGFSHOOTERCORE_API AGGFPickupEquipment : public AGGFInteractableActor
{
    GENERATED_BODY()

protected:
    // 아이템 상호작용 시 추가할 장비 ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 EquipmentID;

protected:
    /* InteractableActor */

    virtual void OnPawnInteract_Implementation(APawn* OtherPawn) override;
};
