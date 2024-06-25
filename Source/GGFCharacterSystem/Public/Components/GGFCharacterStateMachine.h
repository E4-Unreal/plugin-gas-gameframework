// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GGFGameplayStateMachine.h"
#include "GGFCharacterStateMachine.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class GGFCHARACTERSYSTEM_API UGGFCharacterStateMachine : public UGGFGameplayStateMachine
{
    GENERATED_BODY()

public:
    UGGFCharacterStateMachine();
};
