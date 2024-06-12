// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/GGFEquipmentDataSubsystem.h"

#include "GGFDataSubsystem.h"
#include "Data/GGFEquipmentDefinition.h"

void UGGFEquipmentDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    // 서브 시스템 종속성 추가
    Collection.InitializeDependency(UGGFDataSubsystem::StaticClass());

    Super::Initialize(Collection);

    // 데이터 서브 시스템 동기화
    FetchDataSubsystem();
}

bool UGGFEquipmentDataSubsystem::GetData(int32 ID, FGGFEquipmentData& Data)
{
    return UGGFDataSubsystem::GetData(UGGFEquipmentDefinition::StaticClass(), ID, Data);
}

void UGGFEquipmentDataSubsystem::FetchDataSubsystem()
{
    if(UGameInstance* GameInstance = GetGameInstance())
    {
        if(UGGFDataSubsystem* DataSubsystem = GameInstance->GetSubsystem<UGGFDataSubsystem>())
        {
            DataSubsystem->GetCastedDefinitionListAndMap(UGGFEquipmentDefinition::StaticClass(), EquipmentList, EquipmentMap);
        }
    }
}
