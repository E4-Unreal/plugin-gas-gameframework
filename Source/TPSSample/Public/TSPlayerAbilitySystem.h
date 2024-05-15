// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GEPlayerAbilitySystem.h"
#include "TSPlayerAbilitySystem.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class TPSSAMPLE_API UTSPlayerAbilitySystem : public UGEPlayerAbilitySystem
{
    GENERATED_BODY()

public:
    UTSPlayerAbilitySystem();
};
