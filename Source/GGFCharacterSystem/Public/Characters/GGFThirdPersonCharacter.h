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
    /* 서브 오브젝트 이름 */

    static FName CameraBoomName;
    static FName FollowCameraName;

private:
    /* 컴포넌트 */

    // 스프링 암
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCameraBoom, Category = "Component")
    TObjectPtr<USpringArmComponent> CameraBoom;

    // 백 뷰 시점 카메라
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
