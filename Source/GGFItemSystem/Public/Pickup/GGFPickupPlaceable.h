// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFPickup.h"
#include "GGFPickupPlaceable.generated.h"

/**
 * ItemDataSubsystem에 등록된 ItemDefinition 목록 중 ItemID에 해당하는 아이템으로 자동 초기화되는 Pickup 클래스입니다.
 * 스폰 시스템 대신 수동으로 아이템을 배치하거나 테스트가 필요한 경우 이 클래스를 사용하시면 됩니다.
 */
UCLASS()
class GGFITEMSYSTEM_API AGGFPickupPlaceable : public AGGFPickup
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 ItemID;

public:
    virtual void BeginPlay() override;
};
