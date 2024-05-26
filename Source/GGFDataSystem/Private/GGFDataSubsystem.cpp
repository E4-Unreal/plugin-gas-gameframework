// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFDataSubsystem.h"

#include "GGFDataSystemSetting.h"
#include "GGFDefinitionBase.h"

void UGGFDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // 프로젝트 설정 가져오기
    if(UGGFDataSystemSetting* DataSystemSetting = GetMutableDefault<UGGFDataSystemSetting>())
    {
        // 메모리 할당
        DefinitionContainerMap.Reserve(DataSystemSetting->DefinitionDataTableMap.Num());
        for (const auto& [DefinitionClass, DataTable] : DataSystemSetting->DefinitionDataTableMap)
        {
            FGGFDefinitionContainer NewDefinitionContainer;
            NewDefinitionContainer.DataTable = DataTable.LoadSynchronous();
            DefinitionContainerMap.Emplace(DefinitionClass, NewDefinitionContainer);
        }
    }
}

UGGFDefinitionBase* UGGFDataSubsystem::GetOrCreateDefinition(TSubclassOf<UGGFDefinitionBase> DefinitionClass, int32 ID)
{
    // 입력 유효성 검사
    if(DefinitionClass == nullptr || ID < 0 || !DefinitionContainerMap.Contains(DefinitionClass)) return nullptr;

    // 기존 데이터 에셋 검색
    FGGFDefinitionContainer& DefinitionContainer = DefinitionContainerMap[DefinitionClass];
    if(DefinitionContainer.DefinitionMap.Contains(ID)) return DefinitionContainer.DefinitionMap[ID];

    // 새로운 데이터 에셋 생성
    UGGFDefinitionBase* NewDefinition = NewObject<UGGFDefinitionBase>(this, DefinitionClass);
    if(!NewDefinition->InitFromDataTable(DefinitionContainer.DataTable, ID)) return nullptr;

    // 새로운 데이터 에셋 유효성 검사
    if(NewDefinition->IsNotValid()) return nullptr;

    // 새로운 데이터 에셋 저장
    DefinitionContainer.DefinitionMap.Emplace(ID, NewDefinition);
    return NewDefinition;
}

TArray<UGGFDefinitionBase*> UGGFDataSubsystem::GetOrCreateAllDefinitions(TSubclassOf<UGGFDefinitionBase> DefinitionClass)
{
    // 변수 초기화
    TArray<UGGFDefinitionBase*> Definitions;

    // 입력 유효성 검사
    if(DefinitionClass == nullptr || !DefinitionContainerMap.Contains(DefinitionClass)) return Definitions;

    // 데이터 테이블에 등록된 모든 ID 확인
    TArray<FName> RowNames = DefinitionContainerMap[DefinitionClass].DataTable->GetRowNames();

    // 메모리 할당
    Definitions.Reserve(RowNames.Num());

    // Definition 생성
    for (const FName& RowName : RowNames)
    {
        int32 ID = FCString::Atoi(*RowName.ToString());
        Definitions.Emplace(GetOrCreateDefinition(DefinitionClass, ID));
    }

    return Definitions;
}

FGGFDataTableRowBase* UGGFDataSubsystem::GetDirectData(TSubclassOf<UGGFDefinitionBase> DefinitionClass, int32 ID)
{
    // 프로젝트 설정 가져오기
    if(UGGFDataSystemSetting* DataSystemSetting = GetMutableDefault<UGGFDataSystemSetting>())
    {
        for (const auto& [SettingDefinitionClass, SettingDataTable] : DataSystemSetting->DefinitionDataTableMap)
        {
            // 일치 여부 확인
            if(SettingDefinitionClass != DefinitionClass) continue;

            // 데이터 테이블에서 데이터 가져오기
            UDataTable* DataTable = SettingDataTable.LoadSynchronous();
            return DataTable->FindRow<FGGFDataTableRowBase>(FName(FString::FromInt(ID)), "");
        }
    }

    return nullptr;
}
