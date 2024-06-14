// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GGFCameraComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSetFOVFinishedSignature);

// TODO 다른 모듈로 이전
/**
 * FOV 설정 시 부드럽게 전환되는 기능이 구현된 카메라 컴포넌트입니다.
 */
UCLASS()
class GGFEQUIPMENTSYSTEM_API UGGFCameraComponent : public UCameraComponent
{
    GENERATED_BODY()

public:
    // SetFieldOfView 종료 델리게이트
    UPROPERTY(BlueprintAssignable)
    FOnSetFOVFinishedSignature OnSetFOVFinished;

    // FOV 보간 속도
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float InterpSpeed = 20;

protected:
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

    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE float GetDefaultFOV() const { return DefaultFOV; }
};
