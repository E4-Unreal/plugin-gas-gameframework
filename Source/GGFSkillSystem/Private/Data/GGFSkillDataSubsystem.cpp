// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/GGFSkillDataSubsystem.h"

#include "GGFDataSubsystem.h"
#include "Data/GGFSkillDefinition.h"

void UGGFSkillDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    // 서브 시스템 종속성 추가
    Collection.InitializeDependency(UGGFDataSubsystem::StaticClass());

    Super::Initialize(Collection);

    // 데이터 서브 시스템 동기화
    FetchDataSubsystem();
}

const FGGFSkillData& UGGFSkillDataSubsystem::GetData(int32 ID)
{
    if(auto Data = UGGFDataSubsystem::GetData<FGGFSkillData>(UGGFSkillDefinition::StaticClass(), ID))
    {
        return *Data;
    }

    return FGGFSkillData::EmptyData;
}

void UGGFSkillDataSubsystem::FetchDataSubsystem()
{
    if(UGameInstance* GameInstance = GetGameInstance())
    {
        if(UGGFDataSubsystem* DataSubsystem = GameInstance->GetSubsystem<UGGFDataSubsystem>())
        {
            DataSubsystem->GetCastedDefinitionListAndMap(UGGFSkillDefinition::StaticClass(), SkillList, SkillMap);
        }
    }
}
