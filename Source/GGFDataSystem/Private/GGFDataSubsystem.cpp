// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFDataSubsystem.h"

#include "GGFDataSystemSetting.h"
#include "GGFDefinitionBase.h"

/* GGFDefinitionContainer */

bool FGGFDefinitionContainer::Init(UObject* Outer, TSubclassOf<UGGFDefinitionBase> DefinitionClass, UDataTable* DataTable)
{
    // 유효성 검사
    if(DefinitionClass == nullptr || DataTable == nullptr) return false;

    // 지역 변수 초기화
    const TArray<FName>& RowNames = DataTable->GetRowNames();
    const int32 MaxNum = RowNames.Num();

    // 메모리 할당
    List.Reserve(MaxNum);
    Map.Reserve(MaxNum);

    // Definition 생성
    for (const FName& RowName : RowNames)
    {
        int32 DefinitionID = FCString::Atoi(*RowName.ToString());

        // 새로운 데이터 에셋 생성 및 초기화
        if(auto NewDefinition = NewObject<UGGFDefinitionBase>(Outer, DefinitionClass))
        {
            if(NewDefinition->InitFromDataTable(DataTable, DefinitionID) && NewDefinition->IsValid())
            {
                List.Emplace(NewDefinition);
                Map.Emplace(NewDefinition->GetID(), NewDefinition);
            }
        }
    }

    return true;
}

/* GGFDataSubsystem */

FGGFDefinitionContainer UGGFDataSubsystem::EmptyDefinitionContainer;

void UGGFDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // 프로젝트 설정 가져오기
    FetchProjectSettings();
}

void UGGFDataSubsystem::FetchProjectSettings()
{
    // 프로젝트 설정 가져오기
    if(UGGFDataSystemSetting* DataSystemSetting = GetMutableDefault<UGGFDataSystemSetting>())
    {
        // 메모리 할당
        DefinitionContainerMap.Reserve(DataSystemSetting->DefinitionDataTableMap.Num());
        for (const auto& [DefinitionClass, DataTable] : DataSystemSetting->DefinitionDataTableMap)
        {
            // 데이터 테이블로부터 데이터 에셋 생성
            CreateDefinitionsFromDataTable(DefinitionClass, DataTable.LoadSynchronous());
        }
    }
}

void UGGFDataSubsystem::CreateDefinitionsFromDataTable(TSubclassOf<UGGFDefinitionBase> DefinitionClass,
    UDataTable* DataTable)
{
    FGGFDefinitionContainer NewDefinitionContainer;
    NewDefinitionContainer.Init(this, DefinitionClass, DataTable);
    DefinitionContainerMap.Emplace(DefinitionClass, NewDefinitionContainer);
}

UDataTable* UGGFDataSubsystem::GetDataTable(TSubclassOf<UGGFDefinitionBase> DefinitionClass)
{
    // 프로젝트 설정에서 데이터 테이블 가져오기
    if(UGGFDataSystemSetting* DataSystemSetting = GetMutableDefault<UGGFDataSystemSetting>())
    {
        return DataSystemSetting->DefinitionDataTableMap.Contains(DefinitionClass) ? DataSystemSetting->DefinitionDataTableMap[DefinitionClass].LoadSynchronous() : nullptr;
    }

    return nullptr;
}

UGGFDefinitionBase* UGGFDataSubsystem::GetDefinitionBase(TSubclassOf<UGGFDefinitionBase> DefinitionClass, int32 ID) const
{
    // 입력 유효성 검사
    if(DefinitionClass == nullptr || ID < 0) return nullptr;

    // 데이터 검색
    if(!(DefinitionContainerMap.Contains(DefinitionClass) && DefinitionContainerMap[DefinitionClass].Map.Contains(ID))) return nullptr;

    // 데이터 반환
    return DefinitionContainerMap[DefinitionClass].Map[ID];
}

const TArray<UGGFDefinitionBase*>& UGGFDataSubsystem::GetDefinitionBaseList(
    TSubclassOf<UGGFDefinitionBase> DefinitionClass) const
{
    // 입력 유효성 검사
    if(DefinitionClass == nullptr) return EmptyDefinitionContainer.List;

    // 데이터 검색
    if(!DefinitionContainerMap.Contains(DefinitionClass)) return EmptyDefinitionContainer.List;

    // 데이터 반환
    return DefinitionContainerMap[DefinitionClass].List;
}

const TMap<int32, UGGFDefinitionBase*>& UGGFDataSubsystem::GetDefinitionBaseMap(
    TSubclassOf<UGGFDefinitionBase> DefinitionClass) const
{
    // 입력 유효성 검사
    if(DefinitionClass == nullptr) return EmptyDefinitionContainer.Map;

    // 데이터 검색
    if(!DefinitionContainerMap.Contains(DefinitionClass)) return EmptyDefinitionContainer.Map;

    // 데이터 반환
    return DefinitionContainerMap[DefinitionClass].Map;
}
