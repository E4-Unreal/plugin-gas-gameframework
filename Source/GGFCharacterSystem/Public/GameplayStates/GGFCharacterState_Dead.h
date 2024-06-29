// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayStates/GGFGS_Dead.h"
#include "GGFCharacterState_Dead.generated.h"

/**
 * 캐릭터 죽음 상태
 */
UCLASS()
class GGFCHARACTERSYSTEM_API UGGFCharacterState_Dead : public UGGFGS_Dead
{
    GENERATED_BODY()

protected:
    /* GameplayState */

    virtual void OnEnter_Implementation() override;
    virtual void OnExit_Implementation() override;
};
