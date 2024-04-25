// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFItemDefinition.h"
#include "GGFItemConfig_Inventory.generated.h"

/**
 * 인벤토리 아이템 전용 데이터 테이블 구조체
 */
USTRUCT()
struct GGFINVENTORYSYSTEM_API FGGFInventoryItemTableRow : public FTableRowBase
{
    GENERATED_BODY()

    // 인벤토리 슬롯 하나에 담을 수 있는 최대 아이템 개수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 MaxStack;

    // 인벤토리 슬롯 UI에 표시될 아이템 아이콘
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UTexture2D> Icon;

    // 인벤토리 슬롯 UI에 표시될 아이템 설명
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    FGGFInventoryItemTableRow()
    {
        MaxStack = 1;
        Icon = nullptr;
        Description = FText::GetEmpty();
    }
};

/**
 * 인벤토리 아이템 전용 구조체
 */
USTRUCT(BlueprintType)
struct GGFINVENTORYSYSTEM_API FInventoryItemData
{
    GENERATED_BODY()

    // 인벤토리 슬롯 하나에 담을 수 있는 최대 아이템 개수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 MaxStack;

    // 인벤토리 슬롯 UI에 표시될 아이템 아이콘
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UTexture2D> Icon;

    // 인벤토리 슬롯 UI에 표시될 아이템 설명
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    bool IsValid() const { return MaxStack >= 1; }
    bool IsNotValid() const { return !IsValid(); }

    FORCEINLINE FInventoryItemData& operator=(const FGGFInventoryItemTableRow& InventoryItemTableRow)
    {
        MaxStack = InventoryItemTableRow.MaxStack;
        Icon = InventoryItemTableRow.Icon;
        Description = InventoryItemTableRow.Description;

        return *this;
    }
};

/**
 * 인벤토리 아이템 전용 데이터 에셋
 */
UCLASS()
class GGFINVENTORYSYSTEM_API UGGFItemConfig_Inventory : public UGGFItemConfig
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetInventoryData)
    FInventoryItemData InventoryItemData;

public:
    virtual bool InitializeFromDataTable(FTableRowBase* Data) override;

public:
    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FInventoryItemData& GetInventoryData() const { return InventoryItemData; }

    virtual bool IsValid() const override { return InventoryItemData.IsValid(); }
};
