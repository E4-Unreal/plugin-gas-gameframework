// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFCharacterAnimInstance.h"
#include "GGFTPSAnimInstance.generated.h"

/**
 * TPS 전용 캐릭터 애님 인스턴스 클래스
 */
UCLASS()
class GGFANIMATIONSYSTEM_API UGGFTPSAnimInstance : public UGGFCharacterAnimInstance
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config|Weapon")
    FName LeftHandSocketName = "hand_l";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Animation")
    FName DisableLeftHandIKCurveName = "DisableLeftHandIK";

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Weapon", Transient)
    bool bEnableLeftHandIK;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Weapon", Transient)
    FTransform LeftHandTransform;

public:
    /* AnimInstance */

    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
    /* 메서드 */

    virtual void CalculateLeftHandIK(float DeltaSeconds);
};
