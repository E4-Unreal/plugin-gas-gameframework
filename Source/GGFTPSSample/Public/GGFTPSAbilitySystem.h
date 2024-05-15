// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GEPlayerAbilitySystem.h"
#include "GGFTPSAbilitySystem.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class GGFTPSSAMPLE_API UGGFTPSAbilitySystem : public UGEPlayerAbilitySystem
{
    GENERATED_BODY()

public:
    UGGFTPSAbilitySystem();
};
