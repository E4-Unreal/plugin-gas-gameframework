// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "GESpringArmComponent.generated.h"

/**
 * 카메라 랙 기능이 기본 활성화되어 있으며 Z축에만 적용될 수 있는 설정이 추가된 스프링 암 컴포넌트입니다.
 * Crouch, UnCrouch 호출 시 부드러운 카메라 이동을 위해 카메라 랙 기능이 필요하지만 좌우로 달릴 때는 불필요하다고 느껴질 때 사용하면 유용합니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GASGAMEFRAMEWORK_API UGESpringArmComponent : public USpringArmComponent
{
    GENERATED_BODY()

    // true 설정 시 카메라 랙 기능이 Z축에만 적용됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true))
    bool bLimitCameraLagToZ = true;

public:
    UGESpringArmComponent();

protected:
    virtual void UpdateDesiredArmLocation(bool bDoTrace, bool bDoLocationLag, bool bDoRotationLag, float DeltaTime) override;
};
