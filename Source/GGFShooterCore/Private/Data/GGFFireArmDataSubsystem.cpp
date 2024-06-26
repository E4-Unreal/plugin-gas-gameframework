﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/GGFFireArmDataSubsystem.h"

#include "GGFDataSubsystem.h"
#include "Data/GGFFireArmDefinition.h"

void UGGFFireArmDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    // 서브 시스템 종속성 추가
    Collection.InitializeDependency(UGGFDataSubsystem::StaticClass());

    Super::Initialize(Collection);

    // 데이터 서브 시스템 동기화
    FetchDataSubsystem();
}

const FGGFFireArmData& UGGFFireArmDataSubsystem::GetData(int32 ID)
{
    if(auto Data = UGGFDataSubsystem::GetData<FGGFFireArmData>(UGGFFireArmDefinition::StaticClass(), ID))
    {
        return *Data;
    }

    return FGGFFireArmData::EmptyFireArmData;
}

void UGGFFireArmDataSubsystem::FetchDataSubsystem()
{
    if(UGameInstance* GameInstance = GetGameInstance())
    {
        if(UGGFDataSubsystem* DataSubsystem = GameInstance->GetSubsystem<UGGFDataSubsystem>())
        {
            DataSubsystem->GetCastedDefinitionListAndMap(UGGFFireArmDefinition::StaticClass(), FireArmList, FireArmMap);
        }
    }
}
