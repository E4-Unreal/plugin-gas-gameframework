// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GGFCameraComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSetFOVFinishedSignature);

/**
 * FOV 보간 기능과 카메라가 바라보고 있는 목표물을 반환하는 메서드가 구현된 카메라 컴포넌트입니다.
 */
UCLASS()
class GGFCORE_API UGGFCameraComponent : public UCameraComponent
{
    GENERATED_BODY()

public:
    // SetFieldOfView 종료 델리게이트
    UPROPERTY(BlueprintAssignable)
    FOnSetFOVFinishedSignature OnSetFOVFinished;

    // FOV 보간 속도
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FOV")
    float InterpSpeed = 20;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Trace")
    TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float TraceOffset = 100;

protected:
#if WITH_EDITORONLY_DATA
    // 디버그 라인 표시를 위한 옵션
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Debug")
    bool bShowDebug = false;

    // Tick마다 디버그 라인 표시
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Debug", meta = (EditConditionHides = bShowDebug))
    bool bUseTick = false;

    // 디버그 라인 표시 시간으로 bUseTick = false 인 경우에 사용됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float LifeTime = 3;
#endif

    // 현재 FOV가 보간중인 상태인지 나타냅니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    bool bInterpolatingFOV = false;

    // 기본 FOV
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDefaultFOV, Category = "State", Transient)
    float DefaultFOV;

    // 목표 FOV
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    float TargetFOV;

public:
    UGGFCameraComponent();

    /* ActorComponent */

    virtual void InitializeComponent() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    /* CameraComponent */

    virtual void SetFieldOfView(float InFieldOfView) override;

    /* API */

    UFUNCTION(BlueprintPure)
    bool IsInterpolatingFOV() const { return bInterpolatingFOV; }

    // 현재 카메라가 바라보고 있는 목표물 위치 반환
    UFUNCTION(BlueprintPure)
    virtual FVector GetTargetLocation() const;

    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE float GetDefaultFOV() const { return DefaultFOV; }
};
