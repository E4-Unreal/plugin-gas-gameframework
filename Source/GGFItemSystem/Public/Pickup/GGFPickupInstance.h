// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFPickup.h"
#include "GGFPickupInstance.generated.h"

/**
 * 자동 초기화를 위한 설정이 가능하며, 스폰 시스템 대신 수동으로 아이템을 배치할 때 사용하실 수 있습니다.
 * 게임 플레이 중이 아닌 경우에도 DefaultItemDefinition 혹은 DefaultItemConfig 설정 즉시 초기화가 이루어지기 때문에
 * 미리 보기 용도로 사용하실 수도 있습니다.
 *
 * 설정 우선 순위는 차례대로 DefaultItemDefinition, DefaultItemConfig 입니다.
 */
UCLASS()
class GGFITEMSYSTEM_API AGGFPickupInstance : public AGGFPickup
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TObjectPtr<UGGFItemDefinition> DefaultItemDefinition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Instanced)
    TObjectPtr<UGGFItemConfig_Pickup> DefaultItemConfig;

public:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
