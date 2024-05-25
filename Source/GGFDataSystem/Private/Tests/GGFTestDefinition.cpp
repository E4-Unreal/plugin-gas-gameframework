// Fill out your copyright notice in the Description page of Project Settings.

#include "Tests/GGFTestDefinition.h"

bool UGGFTestDefinition::Internal_InitFromDataTable_Implementation()
{
    if(GetDataTable())
    {
        if(FTestDataTableRow* NewData = GetDataTable()->FindRow<FTestDataTableRow>(FName(FString::FromInt(ID)), ""))
        {
            Data = *NewData;

            return true;
        }
    }

    return false;
}
