// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GGFItemSystemSetting.generated.h"

class UGGFItemConfig;
/**
 *
 */
UCLASS(Config = GASGameFramework)
class GGFITEMSYSTEM_API UGGFItemSystemSetting : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(Config, EditAnywhere, Category = "Config")
    TSoftObjectPtr<UDataTable> ItemDataTable;

    UPROPERTY(Config, EditAnywhere, Category = "Config")
    TMap<TSubclassOf<UGGFItemConfig>, TSoftObjectPtr<UDataTable>> ItemConfigDataTableMap;
};
