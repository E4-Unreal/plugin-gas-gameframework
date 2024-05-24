// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/GEInputManager.h"
#include "GGFInputManager.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class GGFCHARACTERSYSTEM_API UGGFInputManager : public UGEInputManager
{
    GENERATED_BODY()

public:
    UGGFInputManager();
};
