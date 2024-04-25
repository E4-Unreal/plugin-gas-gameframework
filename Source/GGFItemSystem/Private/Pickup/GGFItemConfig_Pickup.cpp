// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup/GGFItemConfig_Pickup.h"

bool UGGFItemConfig_Pickup::InitializeFromDataTable(FTableRowBase* TableRow)
{
    if(FGGFPickupTableRow* PickupTableRow = static_cast<FGGFPickupTableRow*>(TableRow))
    {
        PickupData = *PickupTableRow;

        return true;
    }

    return false;
}
