// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFFireArmDataManager.h"

#include "Logging.h"
#include "Data/GGFFireArmDataSubsystem.h"

void UGGFFireArmDataManager::InitializeComponent()
{
    Super::InitializeComponent();

    bValid = bValid && FireArmDefinition != nullptr;
}

FGGFFireArmData UGGFFireArmDataManager::GetFireArmData() const
{
    if(FireArmDefinition)
    {
        return FireArmDefinition->GetData();
    }
    else
    {
        FGGFFireArmData UncachedData;
        bool bFound = UGGFFireArmDataSubsystem::GetData(ID, UncachedData);

#if WITH_EDITOR
        if(!bFound)
        {
            LOG_ACTOR_COMPONENT_DETAIL(Error, TEXT("해당 ID(%d)에 대응하는 데이터를 찾을 수 없습니다."), ID)
        }
#endif

        return UncachedData;
    }
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
