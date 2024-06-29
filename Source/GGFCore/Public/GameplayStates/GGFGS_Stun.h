// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGS_Snare.h"
#include "GGFGS_Stun.generated.h"

/**
 * 기절 상태 - 행동 불가
 */
UCLASS()
class GGFCORE_API UGGFGS_Stun : public UGGFGS_Snare
{
    GENERATED_BODY()

public:
    UGGFGS_Stun();

protected:
    /* GameplayState */

    virtual void OnEnter_Implementation() override;
    virtual void OnExit_Implementation() override;
};
