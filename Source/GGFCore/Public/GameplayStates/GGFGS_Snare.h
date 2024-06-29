// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFPawnState.h"
#include "GGFGS_Snare.generated.h"

/**
 * 속박 상태 - 이동 불가
 */
UCLASS()
class GGFCORE_API UGGFGS_Snare : public UGGFPawnState
{
    GENERATED_BODY()

public:
    UGGFGS_Snare();

protected:
    /* GameplayState */

    virtual void OnEnter_Implementation() override;
    virtual void OnExit_Implementation() override;
};
