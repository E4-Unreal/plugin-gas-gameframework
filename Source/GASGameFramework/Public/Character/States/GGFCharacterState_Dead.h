// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GEGameplayStateMachine.h"
#include "GGFCharacterState_Dead.generated.h"

/**
 * 캐릭터 죽음 상태
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGGFCharacterState_Dead : public UGECharacterState
{
    GENERATED_BODY()

public:
    UGGFCharacterState_Dead();

    virtual void OnEnter_Implementation() override;
    virtual void OnExit_Implementation() override;
};
