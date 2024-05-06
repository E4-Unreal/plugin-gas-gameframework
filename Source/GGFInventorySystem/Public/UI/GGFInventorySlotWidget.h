// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFInventoryManagerBase.h"
#include "Blueprint/UserWidget.h"
#include "GGFInventorySlotWidget.generated.h"

class UGGFInventoryItemConfig;
class UTextBlock;
class UImage;

/**
 * 인벤토리 슬롯 UI
 */
UCLASS()
class GGFINVENTORYSYSTEM_API UGGFInventorySlotWidget : public UUserWidget
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetIconImage, meta = (BindWidget))
    TObjectPtr<UImage> IconImage;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetAmountText, meta = (BindWidget))
    TObjectPtr<UTextBlock> AmountText;

    // 인벤토리 슬롯 번호
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetSlotIndex)
    int32 SlotIndex;

    // 인벤토리 아이템 정보
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetInventoryItem)
    FGGFInventoryItem InventoryItem;

public:
    UFUNCTION(BlueprintCallable)
    virtual void SetInventorySlot(const int32 InSlotIndex, const FGGFInventoryItem& InInventoryItem);

protected:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Update();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetIconImage();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetAmountText();

public:
    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetSlotIndex() const { return SlotIndex; }

    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FGGFInventoryItem& GetInventoryItem() const { return InventoryItem; }

protected:
    UFUNCTION(BlueprintGetter)
    UImage* GetIconImage() const { return IconImage; }

    UFUNCTION(BlueprintGetter)
    UTextBlock* GetAmountText() const { return AmountText; }
};
