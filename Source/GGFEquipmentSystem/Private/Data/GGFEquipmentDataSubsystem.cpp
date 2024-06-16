// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/GGFEquipmentDataSubsystem.h"

#include "GGFDataSubsystem.h"
#include "Data/GGFEquipmentDefinition.h"
#include "Data/GGFWeaponDefinition.h"

void UGGFEquipmentDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    // 서브 시스템 종속성 추가
    Collection.InitializeDependency(UGGFDataSubsystem::StaticClass());

    Super::Initialize(Collection);

    // 데이터 서브 시스템 동기화
    FetchDataSubsystem();
}

const FGGFEquipmentData& UGGFEquipmentDataSubsystem::GetEquipmentData(int32 ID)
{
    if(auto Data = UGGFDataSubsystem::GetData<FGGFEquipmentData>(UGGFEquipmentDefinition::StaticClass(), ID))
    {
        return *Data;
    }

    return FGGFEquipmentData::EmptyEquipmentData;
}

const FGGFWeaponData& UGGFEquipmentDataSubsystem::GetWeaponData(int32 ID)
{
    if(auto Data = UGGFDataSubsystem::GetData<FGGFWeaponData>(UGGFWeaponDefinition::StaticClass(), ID))
    {
        return *Data;
    }

    return FGGFWeaponData::EmptyWeaponData;
}

void UGGFEquipmentDataSubsystem::FetchDataSubsystem()
{
    if(UGameInstance* GameInstance = GetGameInstance())
    {
        if(UGGFDataSubsystem* DataSubsystem = GameInstance->GetSubsystem<UGGFDataSubsystem>())
        {
            DataSubsystem->GetCastedDefinitionListAndMap(UGGFEquipmentDefinition::StaticClass(), EquipmentList, EquipmentMap);
            DataSubsystem->GetCastedDefinitionListAndMap(UGGFWeaponDefinition::StaticClass(), WeaponList, WeaponMap);
        }
    }
}
