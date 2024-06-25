// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGameplayStateMachine.h"
#include "GGFPawnStateMachine.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class GGFCORE_API UGGFPawnStateMachine : public UGGFGameplayStateMachine
{
    GENERATED_BODY()

public:
    UGGFPawnStateMachine();
};
