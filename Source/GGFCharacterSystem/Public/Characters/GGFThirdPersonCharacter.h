// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFPlayerCharacter.h"
#include "Interfaces/GGFAimingInterface.h"
#include "GGFThirdPersonCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 삼인칭 게임을 위한 기본 설정이 적용된 플레이어 캐릭터 클래스
 */
UCLASS()
class GGFCHARACTERSYSTEM_API AGGFThirdPersonCharacter : public AGGFPlayerCharacter,
    public IGGFAimingInterface
{
    GENERATED_BODY()

public:
    /* CameraBoom의 이름으로 다른 클래스로 교체할 때 사용합니다. */
    static FName CameraBoomName;

    /* FollowCamera의 이름으로 다른 클래스로 교체할 때 사용합니다. */
    static FName FollowCameraName;

    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCameraBoom, Category = "Component")
    TObjectPtr<USpringArmComponent> CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetFollowCamera, Category = "Component")
    TObjectPtr<UCameraComponent> FollowCamera;

public:
    AGGFThirdPersonCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* GGFAimingInterface */
    virtual void GetTarget_Implementation(FVector& Target) override;

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
