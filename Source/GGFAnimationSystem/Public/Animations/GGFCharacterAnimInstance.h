// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFAnimInstanceBase.h"
#include "GGFCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;

/**
 * 기본 캐릭터 애님 인스턴스 클래스
 */
UCLASS()
class GGFANIMATIONSYSTEM_API UGGFCharacterAnimInstance : public UGGFAnimInstanceBase
{
    GENERATED_BODY()

    /* 레퍼런스 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetOwningCharacter, Category = "Reference", Transient)
    TObjectPtr<ACharacter> OwningCharacter;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetOwningCharacterMovement, Category = "Reference", Transient)
    TObjectPtr<UCharacterMovementComponent> OwningCharacterMovement;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Character")
    bool bUseControllerRotationYaw = true;

    // 에임 오프셋 보간 속도
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config|Character")
    float InterpSpeed = 15;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Character", Transient)
    FVector Velocity;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Character", Transient)
    float GroundSpeed;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Character", Transient)
    float Direction;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Character", Transient)
    bool bShouldMove;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Character", Transient)
    bool bFalling;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Character", Transient)
    bool bCrouching;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Character", Transient)
    float YawOffset;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Character", Transient)
    float PitchOffset;

public:
    /* AnimInstance */

    virtual void NativeInitializeAnimation() override;
    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

    /* GGFAnimInstanceBase */

    virtual FORCEINLINE bool IsValid() const override { return Super::IsValid() && OwningCharacter != nullptr && OwningCharacterMovement != nullptr; }

    /* 메서드 */

    virtual void CalculateVelocity(float DeltaSeconds);
    virtual void CalculateAimOffset(float DeltaSeconds);
    virtual void FetchCharacterMovement(float DeltaSeconds);

protected:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE ACharacter* GetOwningCharacter() const { return OwningCharacter; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UCharacterMovementComponent* GetOwningCharacterMovement() const { return OwningCharacterMovement; }
};
