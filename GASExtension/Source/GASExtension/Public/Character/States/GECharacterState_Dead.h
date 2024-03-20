// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GECharacterState.h"
#include "GECharacterState_Dead.generated.h"

/**
 *
 */
UCLASS()
class GASEXTENSION_API UGECharacterState_Dead : public UGECharacterState
{
    GENERATED_BODY()

public:
    UGECharacterState_Dead();

protected:
    /* GECharacterState */
    virtual void OnEnter_Implementation(ACharacter* AvatarCharacter) override;
    virtual void OnExit_Implementation(ACharacter* AvatarCharacter) override;
};
