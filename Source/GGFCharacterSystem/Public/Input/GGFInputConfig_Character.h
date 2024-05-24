// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/GEInputConfig.h"
#include "GGFInputConfig_Character.generated.h"

/**
 * 캐릭터 전용 입력 에셋 설정을 위한 데이터 에셋으로 GGFCharacter에 의존성을 가지고 있습니다.
 */
UCLASS()
class GGFCHARACTERSYSTEM_API UGGFInputConfig_Character : public UGEInputConfig
{
    GENERATED_BODY()

protected:
    // 움직임 입력 액션
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> MoveAction;

    // 회전 입력 액션
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> LookAction;

    // 점프 입력 액션
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> JumpAction;

    // 앉기 입력 액션
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> CrouchAction;

protected:
    virtual void OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent) override;
};
