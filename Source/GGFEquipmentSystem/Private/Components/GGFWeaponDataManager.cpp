// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFWeaponDataManager.h"

#include "Data/GGFEquipmentDataSubsystem.h"
#include "Data/GGFWeaponDefinition.h"
#include "Logging.h"

void UGGFWeaponDataManager::InitializeComponent()
{
    Super::InitializeComponent();

    bValid = bValid && WeaponDefinition != nullptr;
}

const FGGFWeaponData& UGGFWeaponDataManager::GetWeaponData() const
{
    return WeaponDefinition ? WeaponDefinition->GetData() : UGGFEquipmentDataSubsystem::GetWeaponData(ID);
}

void UGGFWeaponDataManager::FetchData()
{
    Super::FetchData();

    // 중복 호출 방지
    if(WeaponDefinition && WeaponDefinition->GetID() == ID) return;

    // 초기화
    WeaponDefinition = nullptr;

    // 데이터 가져오기
    if(auto DataSubsystem = GetDataSubsystem<UGGFEquipmentDataSubsystem>())
    {
        WeaponDefinition = DataSubsystem->GetWeaponDefinition(ID);
    }
}
