// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFCharacter.h"
#include "Interface/GGFCharacterMeshInterface.h"
#include "Weapon/Interface/GGFAimingInterface.h"
#include "GGFDefaultCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

// TODO AimingInterface를 크로스헤어 컴포넌트로 분리
/*
 * 1인칭, 3인칭 모두 사용 가능한 캐릭터 클래스입니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API AGGFDefaultCharacter : public AGGFCharacter,
    public IGGFAimingInterface,
    public IGGFCharacterMeshInterface
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

public:
    AGGFDefaultCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

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

    /* GGFCharacterMeshInterface */
    FORCEINLINE virtual USkeletalMeshComponent* GetFirstPersonArmsMesh_Implementation() const override { return FirstPersonArms; }
    FORCEINLINE virtual USkeletalMeshComponent* GetFirstPersonLegsMesh_Implementation() const override { return FirstPersonLegs; }
    FORCEINLINE virtual USkeletalMeshComponent* GetThirdPersonFullBodyMesh_Implementation() const override { return GetMesh(); }
};
