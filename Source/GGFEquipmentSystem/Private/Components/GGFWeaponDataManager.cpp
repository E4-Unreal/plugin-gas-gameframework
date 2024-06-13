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

FGGFWeaponData UGGFWeaponDataManager::GetWeaponData() const
{
    if(WeaponDefinition)
    {
        return WeaponDefinition->GetData();
    }
    else
    {
        FGGFWeaponData UncachedData;
        bool bFound = UGGFEquipmentDataSubsystem::GetWeaponData(ID, UncachedData);

#if WITH_EDITOR
        if(!bFound)
        {
            LOG_ACTOR_COMPONENT_DETAIL(Error, TEXT("해당 ID(%d)에 대응하는 데이터를 찾을 수 없습니다."), ID)
        }
#endif

        return UncachedData;
    }
}

void UGGFWeaponDataManager::SetID(int32 NewID)
{
    // 중복 호출 방지
    if(WeaponDefinition && WeaponDefinition->GetID() == NewID) return;

    // 데이터 가져오기
    if(auto DataSubsystem = GetDataSubsystem<UGGFEquipmentDataSubsystem>())
    {
        WeaponDefinition = DataSubsystem->GetWeaponDefinition(ID);
    }

    Super::SetID(NewID);
}
