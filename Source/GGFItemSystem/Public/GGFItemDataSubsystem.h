// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GGFItemDataSubsystem.generated.h"

class UGGFItemConfig;
class UGGFItemDefinition;
/**
 * 런타임에 데이터 테이블로부터 데이터 에셋 생성 및 관리를 담당하는 서브 시스템 클래스입니다.
 */
UCLASS()
class GGFITEMSYSTEM_API UGGFItemDataSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

protected:
    UPROPERTY(Transient)
    TObjectPtr<UDataTable> ItemDataTable;

    UPROPERTY(Transient)
    TMap<TSubclassOf<UGGFItemConfig>, TObjectPtr<UDataTable>> ItemConfigDataTableMap;

    UPROPERTY(Transient)
    TMap<int32, TObjectPtr<UGGFItemDefinition>> ItemDefinitions;

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

protected:
    virtual void CreateItemDefinition(int32 ID);
    virtual TArray<TObjectPtr<UGGFItemConfig>> CreateItemConfigs(int32 ID);

public:
    UFUNCTION(BlueprintCallable)
    UGGFItemDefinition* GetOrCreateItemDefinition(int32 ID);
};
