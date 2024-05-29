// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GGFThirdPersonCharacter_Retarget.h"
#include "TSPlayerCharacter_Retarget.generated.h"

UCLASS()
class TPSSAMPLE_API ATSPlayerCharacter_Retarget : public AGGFThirdPersonCharacter_Retarget
{
    GENERATED_BODY()

public:
    ATSPlayerCharacter_Retarget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
