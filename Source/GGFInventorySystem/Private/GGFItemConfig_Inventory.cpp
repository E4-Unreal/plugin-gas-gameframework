// Fill out your copyright notice in the Description page of Project Settings.


#include "GGFItemConfig_Inventory.h"

bool UGGFItemConfig_Inventory::InitializeFromDataTable(FTableRowBase* Data)
{
    if(FGGFInventoryItemTableRow* InventoryItemTableRow = static_cast<FGGFInventoryItemTableRow*>(Data))
    {
        InventoryItemData = *InventoryItemTableRow;

        return true;
    }

    return false;
}
