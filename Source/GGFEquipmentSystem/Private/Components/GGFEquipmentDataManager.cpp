// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFEquipmentDataManager.h"

#include "Data/GGFEquipmentDataSubsystem.h"
#include "Data/GGFEquipmentDefinition.h"
#include "Logging.h"

void UGGFEquipmentDataManager::InitializeComponent()
{
    Super::InitializeComponent();

    bValid = Definition != nullptr;
}

FGGFEquipmentData UGGFEquipmentDataManager::GetData() const
{
    if(Definition)
    {
        return Definition->GetData();
    }
    else
    {
        FGGFEquipmentData UncachedData;
        bool bFound = UGGFEquipmentDataSubsystem::GetData(ID, UncachedData);

#if WITH_EDITOR
        if(!bFound)
        {
            LOG_ACTOR_COMPONENT_DETAIL(Error, TEXT("해당 ID(%d)에 대응하는 데이터를 찾을 수 없습니다."), ID)
        }
#endif

        return UncachedData;
    }
}

void UGGFEquipmentDataManager::SetID(int32 NewID)
{
    Definition = nullptr;
    if(auto EquipmentDataSubsystem = GetDataSubsystem<UGGFEquipmentDataSubsystem>())
    {
        Definition = EquipmentDataSubsystem->GetDefinition(ID);
    }

    Super::SetID(NewID);
}
