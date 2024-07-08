// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFActorComponent.h"
#include "Components/TimelineComponent.h"
#include "GGFTimelineComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimelineActivatedSignature, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimelineFinishedSignature);

/**
 * 플로트 커브 기반 타임라인 컴포넌트
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFCORE_API UGGFTimelineComponent : public UGGFActorComponent
{
    GENERATED_BODY()

public:
    /* 델리게이트 */

    UPROPERTY(BlueprintAssignable)
    FTimelineActivatedSignature OnActivated;

    UPROPERTY(BlueprintAssignable)
    FTimelineFinishedSignature OnFinished;

    // 타임라인에서 사용할 플로트 커브
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Timeline")
    TObjectPtr<UCurveFloat> CurveFloat;

    FOnTimelineFloat InterpFunction;
    FOnTimelineEvent FinishedFunction;

    // 타임라인 재생 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Timeline", meta = (EditCondition = bUseCustomDuration))
    float Duration = 2;

protected:
    FTimeline Timeline;

public:
    UGGFTimelineComponent();

    /* ActorComponent */

    virtual void InitializeComponent() override;
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void PlayTimeline(bool bReverse = false, bool bReset = false);

protected:
    UFUNCTION()
    void InternalOnActivated(float Value);

    UFUNCTION()
    void InternalOnFinished();
};
