// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFItemDataSubsystem.h"

#include "GGFItemDefinition.h"
#include "GGFItemSystemSetting.h"

void UGGFItemDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // 프로젝트 설정 가져오기
    if(UGGFItemSystemSetting* ItemSystemSetting = GetMutableDefault<UGGFItemSystemSetting>())
    {
        // ItemDefinition 전용 데이터 테이블 할당
        ItemDataTable = ItemSystemSetting->ItemDataTable.LoadSynchronous();

        // ItemConfig 전용 데이터 테이블 목록 할당
        ItemConfigDataTableMap.Reserve(ItemSystemSetting->ItemConfigDataTableMap.Num());
        for (const auto& [ItemConfigClass, ItemConfigDataTable] : ItemSystemSetting->ItemConfigDataTableMap)
        {
            // 데이터 유효성 검사 후 할당
            UDataTable* LoadedItemConfigDataTable = ItemConfigDataTable.LoadSynchronous();
            if(ItemConfigClass && LoadedItemConfigDataTable)
                ItemConfigDataTableMap.Add(ItemConfigClass, ItemConfigDataTable.LoadSynchronous());
        }
    }
}

void UGGFItemDataSubsystem::Deinitialize()
{
    Super::Deinitialize();
}

void UGGFItemDataSubsystem::CreateItemDefinition(int32 ID)
{
    // 중복 생성 방지
    if(ItemDefinitions.Contains(ID)) return;

    // 데이터 테이블 검사
    if(ItemDataTable == nullptr) return;

    // 데이터 확인
    FString IDString = FString::FromInt(ID);
    FTableRowBase* Data = ItemDataTable->FindRow<FTableRowBase>(FName(IDString), "");
    if(Data == nullptr) return;

    // 데이터 에셋 생성 및 등록
    UGGFItemDefinition* ItemDefinition = NewObject<UGGFItemDefinition>();
    TArray<TObjectPtr<UGGFItemConfig>> ItemConfigs = CreateItemConfigs(ID);
    if(ItemDefinition->InitializeFromDataTable(ID, Data, ItemConfigs))
    {
        FString NewNameString = ItemDefinition->GetName() + " (" + IDString + ")";
        ItemDefinition->Rename(*NewNameString);
        ItemDefinitions.Add(ID, ItemDefinition);
    }
}

TArray<TObjectPtr<UGGFItemConfig>> UGGFItemDataSubsystem::CreateItemConfigs(int32 ID)
{
    TArray<TObjectPtr<UGGFItemConfig>> ItemConfigs;
    ItemConfigs.Reserve(ItemConfigDataTableMap.Num());

    for (const auto& [ItemConfigClass, ItemConfigDataTable] : ItemConfigDataTableMap)
    {
        /* ItemConfigClass, ItemConfigDataTable 유효성 검사는 Initialize에서 이미 진행되었기 때문에 생략합니다. */

        // 데이터 확인
        FString IDString = FString::FromInt(ID);
        FTableRowBase* Data = ItemConfigDataTable->FindRow<FTableRowBase>(FName(IDString), "");
        if(Data == nullptr) continue;

        // 데이터 에셋 생성
        UGGFItemConfig* ItemConfig = NewObject<UGGFItemConfig>(this, ItemConfigClass);
        if(ItemConfig->InitializeFromDataTable(Data))
        {
            FString NewNameString = ItemConfig->GetName() + " (" + IDString + ")";
            ItemConfig->Rename(*NewNameString);
            ItemConfigs.Add(ItemConfig);
        }
    }

    return ItemConfigs;
}

UGGFItemDefinition* UGGFItemDataSubsystem::GetOrCreateItemDefinition(int32 ID)
{
    CreateItemDefinition(ID);

    return ItemDefinitions.Contains(ID) ? ItemDefinitions[ID] : nullptr;
}
