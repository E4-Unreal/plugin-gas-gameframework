// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/GGFCharacterDataSubsystem.h"

#include "GGFDataSubsystem.h"
#include "Data/GGFCharacterDefinition.h"
#include "Data/GGFCharacterSkinDefinition.h"

void UGGFCharacterDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    // 서브 시스템 종속성 추가
    Collection.InitializeDependency(UGGFDataSubsystem::StaticClass());

    Super::Initialize(Collection);

    // 데이터 캐싱
    CachingAllCharacters();
    CachingAllSkins();

    // 데이터 분석
    AnalyzeAllSkins();
}

#if WITH_EDITOR
const FGGFCharacterData* UGGFCharacterDataSubsystem::GetDirectCharacterData(int32 ID)
{
    FGGFDataTableRowBase* DirectData = const_cast<FGGFDataTableRowBase*>(UGGFDataSubsystem::GetDirectData(UGGFCharacterDefinition::StaticClass(), ID));
    return static_cast<FGGFCharacterData*>(DirectData);
}

const TArray<const FGGFCharacterData*> UGGFCharacterDataSubsystem::GetAllDirectCharacterData()
{
    const TArray<const FGGFDataTableRowBase*> AllData = UGGFDataSubsystem::GetAllDirectData(UGGFCharacterDefinition::StaticClass());
    TArray<const FGGFCharacterData*> AllCharacterData;
    AllCharacterData.Reserve(AllData.Num());
    for (auto Data : AllData)
    {
        FGGFDataTableRowBase* TempData = const_cast<FGGFDataTableRowBase*>(Data);
        AllCharacterData.Emplace(static_cast<FGGFCharacterData*>(TempData));
    }

    return AllCharacterData;
}

const FGGFCharacterSkinData* UGGFCharacterDataSubsystem::GetDirectCharacterSkinData(int32 ID)
{
    FGGFDataTableRowBase* DirectData = const_cast<FGGFDataTableRowBase*>(UGGFDataSubsystem::GetDirectData(UGGFCharacterSkinDefinition::StaticClass(), ID));
    return static_cast<FGGFCharacterSkinData*>(DirectData);
}

const TArray<const FGGFCharacterSkinData*> UGGFCharacterDataSubsystem::GetAllDirectCharacterSkinData()
{
    TArray<const FGGFDataTableRowBase*> AllData = UGGFDataSubsystem::GetAllDirectData(UGGFCharacterSkinDefinition::StaticClass());
    TArray<const FGGFCharacterSkinData*> AllSkinData;
    AllSkinData.Reserve(AllData.Num());
    for (auto Data : AllData)
    {
        FGGFDataTableRowBase* TempData = const_cast<FGGFDataTableRowBase*>(Data);
        AllSkinData.Emplace(static_cast<FGGFCharacterSkinData*>(TempData));
    }

    return AllSkinData;
}
#endif

void UGGFCharacterDataSubsystem::CachingAllCharacters()
{
    if(UGameInstance* GameInstance = GetGameInstance())
    {
        if(UGGFDataSubsystem* DataSubsystem = GameInstance->GetSubsystem<UGGFDataSubsystem>())
        {
            // 모든 데이터 에셋 가져오기
            const auto& Definitions = DataSubsystem->GetOrCreateAllDefinitions(UGGFCharacterDefinition::StaticClass());

            // 메모리 할당
            CharacterList.Reserve(Definitions.Num());
            CharacterIDMap.Reserve(Definitions.Num());

            // 데이터 에셋 등록
            for (auto Definition : Definitions)
            {
                UGGFDataSubsystem::CachingDefinition(Definition, CharacterList, CharacterIDMap);
            }
        }
    }
}

void UGGFCharacterDataSubsystem::CachingAllSkins()
{
    if(UGameInstance* GameInstance = GetGameInstance())
    {
        if(UGGFDataSubsystem* DataSubsystem = GameInstance->GetSubsystem<UGGFDataSubsystem>())
        {
            // 모든 데이터 에셋 가져오기
            const auto& Definitions = DataSubsystem->GetOrCreateAllDefinitions(UGGFCharacterSkinDefinition::StaticClass());

            // 메모리 할당
            SkinList.Reserve(Definitions.Num());
            SkinIDMap.Reserve(Definitions.Num());

            // 데이터 에셋 캐싱
            for (auto Definition : Definitions)
            {
                UGGFDataSubsystem::CachingDefinition(Definition, SkinList, SkinIDMap);
            }
        }
    }
}

void UGGFCharacterDataSubsystem::AnalyzeAllSkins()
{
    /* 스킨 데이터 분석 */

    for (auto SkinDefinition : SkinList)
    {
        // 지역 변수 정의
        const int32 SkinID = SkinDefinition->GetID();
        const FGGFCharacterSkinData& Data = SkinDefinition->GetData();

        // 모든 캐릭터가 착용 가능한 경우
        if(Data.AvailableCharacterIDList.IsEmpty())
        {
            UniversalSkinList.Emplace(SkinID);
        }
        else
        {
            // 특정 캐릭터만 착용 가능한 경우
            for (const int32 CharacterID : Data.AvailableCharacterIDList)
            {
                UniqueSkinMap.Emplace(CharacterID, SkinID);
            }
        }

        // 특정 캐릭터만 착용이 불가능한 경우
        for (const int32 CharacterID : Data.ForbiddenCharacterIDList)
        {
            ForbiddenSkinMap.Emplace(CharacterID, SkinID);
        }
    }

    /* 캐싱 */

    for (auto CharacterDefinition : CharacterList)
    {
        RegisterAvailableSkin(CharacterDefinition->GetID());
    }
}

void UGGFCharacterDataSubsystem::RegisterAvailableSkin(int32 CharacterID)
{
    // 해당 캐릭터가 사용 가능한 스킨 목록 가져오기
    TArray<int32> AvailableSkinIDList = UniqueSkinMap.Contains(CharacterID) ? UniqueSkinMap[CharacterID].List : TArray<int32>();

    // 금지된 스킨을 제외한 모든 범용 스킨 목록 추가
    TArray<int32> LocalUniversalSkinList = UniversalSkinList;
    if(ForbiddenSkinMap.Contains(CharacterID))
    {
        // 범용 스킨 목록에서 금지된 스킨 제외
        for (int32 ForbiddenSkinID : ForbiddenSkinMap[CharacterID].List)
        {
            LocalUniversalSkinList.RemoveSwap(ForbiddenSkinID);
        }
    }

    // 사용 가능한 스킨 목록에 추가
    AvailableSkinIDList.Append(LocalUniversalSkinList);

    // 등록
    AvailableSkinMap.Emplace(CharacterID, AvailableSkinIDList);
}
