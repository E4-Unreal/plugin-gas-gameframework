// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEAnimInstance.h"
#include "GECharacterAnimInstance.generated.h"

class UCharacterMovementComponent;

/**
 * 캐릭터 및 캐릭터 움직임 컴포넌트에 대한 레퍼런스를 가지고 있는 캐릭터 전용 애님 인스턴스 클래스입니다.
 */
UCLASS()
class GASEXTENSION_API UGECharacterAnimInstance : public UGEAnimInstance
{
    GENERATED_BODY()

    /* 레퍼런스 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetOwningCharacter, Category = "Reference", Transient)
    TObjectPtr<ACharacter> OwningCharacter;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetOwningCharacterMovement, Category = "Reference", Transient)
    TObjectPtr<UCharacterMovementComponent> OwningCharacterMovement;

public:
    /* AnimInstance */

    virtual void NativeInitializeAnimation() override;

protected:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE ACharacter* GetOwningCharacter() const { return OwningCharacter; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UCharacterMovementComponent* GetOwningCharacterMovement() const { return OwningCharacterMovement; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsValid() const { return OwningCharacter && OwningCharacterMovement; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }
};
