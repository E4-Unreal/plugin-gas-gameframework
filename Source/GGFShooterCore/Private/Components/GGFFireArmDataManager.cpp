// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFFireArmDataManager.h"

#include "Logging.h"
#include "Data/GGFFireArmDataSubsystem.h"

void UGGFFireArmDataManager::InitializeComponent()
{
    Super::InitializeComponent();

    bValid = bValid && FireArmDefinition != nullptr;
}

const FGGFFireArmData& UGGFFireArmDataManager::GetFireArmData() const
{
    return FireArmDefinition ? FireArmDefinition->GetData() : UGGFFireArmDataSubsystem::GetData(ID);
}

void UGGFFireArmDataManager::FetchData()
{
    Super::FetchData();

    // 중복 호출 방지
    if(FireArmDefinition && FireArmDefinition->GetID() == ID) return;

    // 초기화
    FireArmDefinition = nullptr;

    // 데이터 가져오기
    if(auto DataSubsystem = GetDataSubsystem<UGGFFireArmDataSubsystem>())
    {
        FireArmDefinition = DataSubsystem->GetDefinition(ID);
    }
}
