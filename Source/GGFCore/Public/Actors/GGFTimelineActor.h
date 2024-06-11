// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "GGFTimelineActor.generated.h"

/**
 * 타임라인 기능이 포함된 기본 액터 클래스입니다.
 */
UCLASS()
class GGFCORE_API AGGFTimelineActor : public AActor
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetTimeline, Category = "Component")
    TObjectPtr<UTimelineComponent> Timeline;

protected:
    // 타임라인에서 사용할 플로트 커브
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Timeline")
    TObjectPtr<UCurveFloat> TimelineCurveFloat;

    FOnTimelineFloat TimelineInterpFunction;
    FOnTimelineEvent TimelineFinishedFunction;

    // 타임라인 재생 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Timeline")
    bool bUseCustomDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Timeline", meta = (EditCondition = bUseCustomDuration))
    float Duration = 2;

public:
    AGGFTimelineActor();

    /* Actor */

    virtual void PostInitializeComponents() override;

protected:
    /* 메서드 */

    UFUNCTION(BlueprintCallable)
    virtual void PlayTimeline(bool bReverse = false, bool bReset = false);

    /* 이벤트 */

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnTimelineActivated(float Value);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnTimelineFinished();

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UTimelineComponent* GetTimeline() const { return Timeline; }
};
