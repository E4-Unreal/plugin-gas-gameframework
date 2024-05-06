// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFInventoryManagerBase.h"
#include "GGFInventoryManager.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class GGFINVENTORYSYSTEM_API UGGFInventoryManager : public UGGFInventoryManagerBase
{
    GENERATED_BODY()

public:
    UGGFInventoryManager();
};
