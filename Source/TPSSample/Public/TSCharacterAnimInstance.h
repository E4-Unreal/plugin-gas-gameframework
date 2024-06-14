// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animations/GECharacterAnimInstance.h"
#include "TSCharacterAnimInstance.generated.h"

/**
 * TPS Sample 캐릭터 전용 애님 인스턴스 클래스
 */
UCLASS()
class TPSSAMPLE_API UTSCharacterAnimInstance : public UGECharacterAnimInstance
{
    GENERATED_BODY()

protected:
    FVector Velocity;
    float GroundSpeed;
    float Direction;
    bool bShouldMove;
    float YawOffset;
    float PitchOffset;
    FTransform LeftHandTransform;
    bool bCanUseLeftHandTransform;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    float InterpSpeed = 15;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    FName LeftHandSocketName = "hand_l";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName DisableLeftHandIKCurveName = "DisableLeftHandIK";

public:
    /* AnimInstance */

    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
    /* Getter */

    UFUNCTION(BlueprintPure, Category = "Character", meta = (BlueprintThreadSafe))
    FORCEINLINE FVector GetVelocity() const { return Velocity; }

    UFUNCTION(BlueprintPure, Category = "Character", meta = (BlueprintThreadSafe))
    FORCEINLINE float GetGroundSpeed() const { return GroundSpeed; }

    UFUNCTION(BlueprintPure, Category = "Character", meta = (BlueprintThreadSafe))
    FORCEINLINE float GetDirection() const { return Direction; }

    UFUNCTION(BlueprintPure, Category = "Character", meta = (BlueprintThreadSafe))
    FORCEINLINE bool ShouldMove() const { return bShouldMove; }

    UFUNCTION(BlueprintPure, Category = "Character", meta = (BlueprintThreadSafe))
    FORCEINLINE float GetYawOffset() const { return YawOffset; }

    UFUNCTION(BlueprintPure, Category = "Character", meta = (BlueprintThreadSafe))
    FORCEINLINE float GetPitchOffset() const { return PitchOffset; }

    UFUNCTION(BlueprintPure, Category = "Character", meta = (BlueprintThreadSafe))
    FORCEINLINE FTransform GetLeftHandTransform() const { return LeftHandTransform; }

    UFUNCTION(BlueprintPure, Category = "Character", meta = (BlueprintThreadSafe))
    FORCEINLINE bool CanUseLeftHandTransform() const { return bCanUseLeftHandTransform; }
};
