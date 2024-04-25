// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GGFItemDefinition.generated.h"

USTRUCT()
struct GGFITEMSYSTEM_API FGGFItemTableRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    FGGFItemTableRow()
    {
        DisplayName = FText::GetEmpty();
    }
};

/**
 * 각 컴포넌트에서 필요한 데이터를 서브 클래스에서 정의하여 사용합니다.
 */
UCLASS(EditInlineNew, Abstract)
class GGFITEMSYSTEM_API UGGFItemConfig : public UDataAsset
{
    GENERATED_BODY()

public:
    virtual bool InitializeFromDataTable(FTableRowBase* Data) { return false; }

    UFUNCTION(BlueprintPure)
    virtual bool IsValid() const { return true; }

    UFUNCTION(BlueprintPure)
    bool IsNotValid() const { return !IsValid(); }
};

/**
 * 모든 아이템의 기본 클래스로 ItemConfig 데이터 에셋을 배열로 가지고 있습니다.
 * FindConfigByClass 메서드를 통해 각 컴포넌트에서 필요한 ItemConfig 데이터 에셋만 참조하여 사용합니다.
 */
UCLASS(Blueprintable, Const)
class GGFITEMSYSTEM_API UGGFItemDefinition : public UDataAsset
{
    GENERATED_BODY()

protected:
    // 경우에 따라 DisplayName은 중복될 수 있기 때문에 에셋 구분은 ID를 사용합니다.
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetID)
    int32 ID;

    // UI에서 표시될 이름으로 경우에 따라 중복될 수도 있습니다.
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetDisplayName)
    FText DisplayName;

    // 각 컴포넌트 별로 필요한 데이터 에셋 목록
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TArray<TObjectPtr<UGGFItemConfig>> Configs;

    // 주로 테스트를 목적으로 사용되며 검색 우선 순위는 Configs가 더 높습니다.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
    TArray<TObjectPtr<UGGFItemConfig>> InstancedConfigs;

public:
    virtual bool InitializeFromDataTable(int32 InID, FTableRowBase* InData, const TArray<TObjectPtr<UGGFItemConfig>>& InConfigs);

    UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = ConfigClass))
    virtual UGGFItemConfig* FindConfigByClass(TSubclassOf<UGGFItemConfig> ConfigClass);

public:
    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetID() const { return ID; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE FText GetDisplayName() const { return DisplayName; }
};
