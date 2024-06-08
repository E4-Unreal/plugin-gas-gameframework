// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFTriggerBox.h"
#include "GGFAutoTeleporter.generated.h"

class UGGFTeleportComponent;

/**
 * Pawn이 오버랩되는 즉시 목표 위치로 순간이동시키는 액터 클래스입니다.
 */
UCLASS()
class GGFGIMMICKSYSTEM_API AGGFAutoTeleporter : public AGGFTriggerBox
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetTeleportComponent, Category = "Component")
    TObjectPtr<UGGFTeleportComponent> TeleportComponent;

public:
    AGGFAutoTeleporter();

protected:
    /* TriggerBox */

    virtual void OnTriggerBoxBeginOverlapPawn_Implementation(UPrimitiveComponent* OverlappedComponent, APawn* OtherPawn, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFTeleportComponent* GetTeleportComponent() const { return TeleportComponent; }
};
