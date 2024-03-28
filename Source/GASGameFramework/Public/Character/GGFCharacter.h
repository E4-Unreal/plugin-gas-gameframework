// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFCharacterBase.h"
#include "GGFCharacter.generated.h"

struct FInputActionValue;

/*
 * 기본 움직임 및 입력 액션 바인딩만 담당
 */
UCLASS()
class GASGAMEFRAMEWORK_API AGGFCharacter : public AGGFCharacterBase
{
    GENERATED_BODY()

public:
    // 캐릭터 이동
    virtual void Move(const FInputActionValue& Value);

    // 컨트롤러 회전
    virtual void Look(const FInputActionValue& Value);

    // 앉기 입력 이벤트 핸들링
    void ToggleCrouch();
};
