// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFItemDataManager.h"

#include "Data/GGFItemDataSubsystem.h"
#include "Data/GGFItemDefinition.h"

void UGGFItemDataManager::InitializeComponent()
{
    Super::InitializeComponent();

    bValid = Definition != nullptr;
}

const FGGFItemData& UGGFItemDataManager::GetData() const
{
    return Definition ? Definition->GetData() : UGGFItemDataSubsystem::GetData(ID);
}

void UGGFItemDataManager::FetchData()
{
    Super::FetchData();

    // 중복 호출 방지
    if(Definition && Definition->GetID() == ID) return;

    // 초기화
    Definition = nullptr;

    // 데이터 가져오기
    if(auto ItemDataSubsystem = GetDataSubsystem<UGGFItemDataSubsystem>())
    {
        Definition = ItemDataSubsystem->GetDefinition(ID);
    }
}
