// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GECharacter.h"
#include "Weapon/Interface/AimingInterface.h"
#include "GEDefaultCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

// TODO AimingInterface를 크로스헤어 컴포넌트로 분리
/*
 * 1인칭, 3인칭 모두 사용 가능한 캐릭터 클래스입니다.
 */
UCLASS()
class GASEXTENSION_API AGEDefaultCharacter : public AGECharacter, public IAimingInterface
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpringArmComponent> SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> GameViewCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USkeletalMeshComponent> FirstPersonArms;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USkeletalMeshComponent> FirstPersonLegs;

public:
    AGEDefaultCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* AimingInterface */
    virtual void GetTarget_Implementation(FVector& Target) override;
};
