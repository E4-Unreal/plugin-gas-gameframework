// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GGFInventoryItemConfig.generated.h"

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
};

/**
 * 인벤토리 아이템 전용 데이터 에셋
 */
UCLASS()
class GGFINVENTORYSYSTEM_API UGGFInventoryItemConfig : public UDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetInventoryData)
    FInventoryItemData InventoryItemData;

public:
    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FInventoryItemData& GetInventoryData() const { return InventoryItemData; }
};
