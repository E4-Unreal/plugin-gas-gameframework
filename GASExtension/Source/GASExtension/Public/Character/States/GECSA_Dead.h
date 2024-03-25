// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GECharacterStateAbility.h"
#include "GECSA_Dead.generated.h"

/**
 * 캐릭터 죽음 상태
 */
UCLASS()
class GASEXTENSION_API UGECSA_Dead : public UGECharacterStateAbility
{
    GENERATED_BODY()

public:
    UGECSA_Dead();

protected:
    /* GECharacterState */
    virtual void OnEnter_Implementation() override;
    virtual void OnExit_Implementation() override;
};
