// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GGFCharacter.h"
#include "GGFTPSCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * TPS 전용 캐릭터 클래스
 */
UCLASS()
class GGFTPSSAMPLE_API AGGFTPSCharacter : public AGGFCharacter
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
    AGGFTPSCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
