// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFItemDataManager.h"

#include "Data/GGFItemDataSubsystem.h"
#include "Data/GGFItemDefinition.h"
#include "Logging.h"

void UGGFItemDataManager::InitializeComponent()
{
    Super::InitializeComponent();

    bValid = Definition != nullptr;
}

FGGFItemData UGGFItemDataManager::GetData() const
{
    if(Definition)
    {
        return Definition->GetData();
    }
    else
    {
        FGGFItemData UncachedData;
        bool bFound = UGGFItemDataSubsystem::GetData(ID, UncachedData);

#if WITH_EDITOR
        if(!bFound)
        {
            LOG_ACTOR_COMPONENT_DETAIL(Error, TEXT("해당 ID(%d)에 대응하는 데이터를 찾을 수 없습니다."), ID)
        }
#endif

        return UncachedData;
    }
}

void UGGFItemDataManager::SetID(int32 NewID)
{
    Definition = nullptr;
    if(auto ItemDataSubsystem = GetDataSubsystem<UGGFItemDataSubsystem>())
    {
        Definition = ItemDataSubsystem->GetDefinition(ID);
    }

    Super::SetID(NewID);
}
