// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GECharacterMovementBase.h"
#include "GECharacterMovement.generated.h"

/*
 * 앉은 상태에서도 점프가 가능합니다.
 * 또한, 일반적으로 사용되는 설정이 적용되어 있습니다.
 */
UCLASS()
class GASEXTENSION_API UGECharacterMovement : public UGECharacterMovementBase
{
    GENERATED_BODY()

public:
    UGECharacterMovement();

    /* CharacterMovementComponent */

    virtual bool CanAttemptJump() const override;

    virtual bool DoJump(bool bReplayingMoves) override;
};
