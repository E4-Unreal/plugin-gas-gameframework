// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GGFTriggerBox.h"
#include "GGFLevelPortal.generated.h"

/**
 * 플레이어가 진입하게 되면 서버를 설정된 레벨로 이동시키는 포탈
 */
UCLASS()
class GGFGIMMICKSYSTEM_API AGGFLevelPortal : public AGGFTriggerBox
{
    GENERATED_BODY()

public:
    // 이동할 레벨
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UWorld> DestinationLevel;

public:
    AGGFLevelPortal();

protected:
    /* TriggerBase */

    virtual void OnCollisionBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
