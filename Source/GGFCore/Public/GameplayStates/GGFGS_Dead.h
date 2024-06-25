// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGS_Stun.h"
#include "GGFGS_Dead.generated.h"

/**
 * 기본 죽음 상태
 */
UCLASS()
class GGFCORE_API UGGFGS_Dead : public UGGFGS_Stun
{
    GENERATED_BODY()

public:
    UGGFGS_Dead();

protected:
    /* GameplayState */

    virtual void OnEnter_Implementation() override;
    virtual void OnExit_Implementation() override;
};
