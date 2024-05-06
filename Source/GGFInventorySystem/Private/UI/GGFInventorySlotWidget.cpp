// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GGFInventorySlotWidget.h"

#include "GGFInventoryItemConfig.h"
#include "GGFInventoryManagerBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UGGFInventorySlotWidget::SetInventorySlot(const int32 InSlotIndex, const FGGFInventoryItem& InInventoryItem)
{
    SlotIndex = InSlotIndex;
    InventoryItem = InInventoryItem;

    Update();
}

void UGGFInventorySlotWidget::Update_Implementation()
{
    SetIconImage();
    SetAmountText();
}

void UGGFInventorySlotWidget::SetIconImage_Implementation()
{
    if(UGGFInventoryItemConfig* InventoryItemConfig = InventoryItem.InventoryItemConfig)
    {
        IconImage->SetBrushFromTexture(InventoryItemConfig->GetInventoryData().Icon);
    }
}

void UGGFInventorySlotWidget::SetAmountText_Implementation()
{
    AmountText->SetText(FText::FromString(FString::FromInt(InventoryItem.Amount)));
}
