// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFCharacterBase.h"
#include "GGFCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/*
 * 기본 움직임 및 입력 액션 바인딩만 담당
 */
UCLASS()
class GASGAMEFRAMEWORK_API AGGFCharacter : public AGGFCharacterBase
{
    GENERATED_BODY()

    // 기본 입력 매핑 컨텍스트
    UPROPERTY(EditDefaultsOnly, Category = "Config|Input")
    TArray<TObjectPtr<UInputMappingContext>> DefaultMappingContexts;

    // 움직임 입력 액션
    UPROPERTY(EditDefaultsOnly, Category = "Config|Input")
    TObjectPtr<UInputAction> MoveAction;

    // 회전 입력 액션
    UPROPERTY(EditDefaultsOnly, Category = "Config|Input")
    TObjectPtr<UInputAction> LookAction;

    // 점프 입력 액션
    UPROPERTY(EditDefaultsOnly, Category = "Config|Input")
    TObjectPtr<UInputAction> JumpAction;

    // 앉기 입력 액션
    UPROPERTY(EditDefaultsOnly, Category = "Config|Input")
    TObjectPtr<UInputAction> CrouchAction;

public:
    virtual void BeginPlay() override;

protected:
    /* AGGFCharacterBase */
    virtual void SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent) override;

    // 캐릭터 이동
    virtual void Move(const FInputActionValue& Value);

    // 컨트롤러 회전
    virtual void Look(const FInputActionValue& Value);

    // 앉기 입력 이벤트 핸들링
    void ToggleCrouch();
};
