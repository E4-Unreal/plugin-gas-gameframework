// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFTriggerBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GGFTriggerBox.generated.h"

UENUM(BlueprintType)
enum class EGGFPivot : uint8
{
    Center,
    Bottom,
    Top,
    Custom
};

class UBoxComponent;

/**
 * 박스 콜리전 컴포넌트 오버랩 이벤트가 기본 바인딩된 액터 클래스
 */
UCLASS()
class GGFCORE_API AGGFTriggerBox : public AGGFTriggerBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    EGGFPivot TriggerBoxPivot = EGGFPivot::Bottom;

public:
    AGGFTriggerBox(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void OnConstruction(const FTransform& Transform) override;

protected:
    /* 메서드 */

    // TriggerBoxPivot 설정에 따라 BoxCollision 위치 조정
    UFUNCTION(BlueprintCallable)
    virtual void SetBoxCollisionPosition();

public:
    /* Getter */

    UFUNCTION(BlueprintPure)
    FORCEINLINE UBoxComponent* GetBoxCollision() const { return Cast<UBoxComponent>(GetCollision()); }
};
