// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/GGFItemDataSubsystem.h"

#include "GGFDataSubsystem.h"
#include "Data/GGFItemDefinition.h"

void UGGFItemDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    // 서브 시스템 종속성 추가
    Collection.InitializeDependency(UGGFDataSubsystem::StaticClass());

    Super::Initialize(Collection);

    // 데이터 서브 시스템 동기화
    FetchDataSubsystem();
}

const FGGFItemData& UGGFItemDataSubsystem::GetData(int32 ID)
{
    if(auto Data = UGGFDataSubsystem::GetData<FGGFItemData>(UGGFItemDefinition::StaticClass(), ID))
    {
        return *Data;
    }

    return FGGFItemData::EmptyItemData;
}

void UGGFItemDataSubsystem::FetchDataSubsystem()
{
    if(UGameInstance* GameInstance = GetGameInstance())
    {
        if(UGGFDataSubsystem* DataSubsystem = GameInstance->GetSubsystem<UGGFDataSubsystem>())
        {
            DataSubsystem->GetCastedDefinitionListAndMap(UGGFItemDefinition::StaticClass(), ItemList, ItemMap);
        }
    }
}
