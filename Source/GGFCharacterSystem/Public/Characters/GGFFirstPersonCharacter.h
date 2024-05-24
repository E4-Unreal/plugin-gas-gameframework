// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFPlayerCharacter.h"
#include "Interfaces/GGFAimingInterface.h"
#include "Interfaces/GGFCameraInterface.h"
#include "GGFFirstPersonCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

// TODO 전체적으로 재설계 예정
// TODO AimingInterface를 크로스헤어 컴포넌트로 분리
/*
 * 1인칭, 3인칭 모두 사용 가능한 캐릭터 클래스입니다.
 */
UCLASS()
class GGFCHARACTERSYSTEM_API AGGFFirstPersonCharacter : public AGGFPlayerCharacter,
    public IGGFAimingInterface,
    public IGGFCameraInterface
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetSpringArm, Category = "Component")
    TObjectPtr<USpringArmComponent> SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetGameViewCamera, Category = "Component")
    TObjectPtr<UCameraComponent> GameViewCamera;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetFirstPersonArms, Category = "Component")
    TObjectPtr<USkeletalMeshComponent> FirstPersonArms;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetFirstPersonLegs, Category = "Component")
    TObjectPtr<USkeletalMeshComponent> FirstPersonLegs;

protected:
    /* GGFCameraInterface */
    UPROPERTY(EditAnywhere, Category = "Config|Weapon")
    float FOV = 120.f;

    UPROPERTY(EditAnywhere, Category = "Config|Weapon")
    float InterpSpeed = 15.f;

public:
    AGGFFirstPersonCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
    /* Getter */
    UFUNCTION(BlueprintGetter)
    FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UCameraComponent* GetGameViewCamera() const { return GameViewCamera; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USkeletalMeshComponent* GetFirstPersonArms() const { return FirstPersonArms; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USkeletalMeshComponent* GetFirstPersonLegs() const { return FirstPersonLegs; }

public:
    /* GGFAimingInterface */
    virtual void GetTarget_Implementation(FVector& Target) override;

    /* GGFCameraInterface */
    FORCEINLINE virtual float GetFieldOfView_Implementation() const override { return FOV; }
    FORCEINLINE virtual float GetInterpSpeed_Implementation() const override { return InterpSpeed; }
};
