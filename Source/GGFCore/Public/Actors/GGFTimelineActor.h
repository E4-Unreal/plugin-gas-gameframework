// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGFTimelineActor.generated.h"

class UGGFTimelineComponent;

/**
 * 타임라인 기능이 포함된 기본 액터 클래스입니다.
 */
UCLASS()
class GGFCORE_API AGGFTimelineActor : public AActor
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetTimeline, Category = "Component")
    TObjectPtr<UGGFTimelineComponent> Timeline;

public:
    /* Actor */

    virtual void BeginPlay() override;

protected:

    /* 이벤트 */

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnTimelineActivated(float Value);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnTimelineFinished();

public:
    AGGFTimelineActor();

    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFTimelineComponent* GetTimeline() const { return Timeline; }
};
