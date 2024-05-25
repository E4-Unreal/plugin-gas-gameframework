// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GGFDataSystemSetting.generated.h"

class UGGFDefinitionBase;

/**
 * GGFDataSystem에서 사용할 프로젝트 설정 전용 데이터 클래스
 */
UCLASS(Config = GASGameFramework)
class GGFDATASYSTEM_API UGGFDataSystemSetting : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(Config, EditAnywhere, Category = "Config")
    TMap<TSubclassOf<UGGFDefinitionBase>, TSoftObjectPtr<UDataTable>> DefinitionDataTableMap;
};
