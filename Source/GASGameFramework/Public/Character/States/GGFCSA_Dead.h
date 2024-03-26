// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFCharacterStateAbility.h"
#include "GGFCSA_Dead.generated.h"

/**
 * 캐릭터 죽음 상태
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGGFCSA_Dead : public UGGFCharacterStateAbility
{
    GENERATED_BODY()

public:
    UGGFCSA_Dead();

protected:
    /* GGFCharacterState */
    virtual void OnEnter_Implementation() override;
    virtual void OnExit_Implementation() override;
};
