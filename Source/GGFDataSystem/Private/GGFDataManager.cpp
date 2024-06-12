// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFDataManager.h"

void UGGFDataManager::PostInitProperties()
{
    Super::PostInitProperties();

    SetID(ID);
}

void UGGFDataManager::SetID(int32 NewID)
{
    ID = NewID;

    OnIDUpdated.Broadcast(NewID);
}
