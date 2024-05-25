// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GEGameplayStateMachine.h"
#include "GGFCharacterStateMachine.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class GGFCHARACTERSYSTEM_API UGGFCharacterStateMachine : public UGEGameplayStateMachine
{
    GENERATED_BODY()

public:
    UGGFCharacterStateMachine();
};
