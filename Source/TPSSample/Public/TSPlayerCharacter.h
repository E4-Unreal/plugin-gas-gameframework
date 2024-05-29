// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GGFThirdPersonCharacter.h"
#include "TSPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * TPS Sample 전용 캐릭터 클래스
 */
UCLASS()
class TPSSAMPLE_API ATSPlayerCharacter : public AGGFThirdPersonCharacter
{
    GENERATED_BODY()

public:
    ATSPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
