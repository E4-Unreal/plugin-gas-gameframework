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

    // 데이터 서브 시스템 가져오기
    if(UGGFDataSubsystem* DataSubsystem = GetGameInstance()->GetSubsystem<UGGFDataSubsystem>())
    {
        /* 캐릭터 정의 데이터 에셋 */

        // 모든 데이터 에셋 가져오기
        TArray<UGGFDefinitionBase*> Definitions = DataSubsystem->GetOrCreateAllDefinitions(UGGFCharacterDefinition::StaticClass());

        // 메모리 할당
        DefinitionList.Reserve(Definitions.Num());
        DefinitionMap.Reserve(Definitions.Num());

        // 데이터 에셋 캐싱
        for (UGGFDefinitionBase* Definition : Definitions)
        {
            CachingDefinition(CastChecked<UGGFCharacterDefinition>(Definition));
        }

        /* 캐릭터 스킨 데이터 에셋 */

        // 모든 데이터 에셋 가져오기
        Definitions = DataSubsystem->GetOrCreateAllDefinitions(UGGFCharacterSkinDefinition::StaticClass());

        // 메모리 할당
        SkinDefinitionList.Reserve(Definitions.Num());
        SkinDefinitionMap.Reserve(Definitions.Num());

        // 데이터 에셋 캐싱
        for (UGGFDefinitionBase* Definition : Definitions)
        {
            CachingSkinDefinition(CastChecked<UGGFCharacterSkinDefinition>(Definition));
        }
    }
}

TArray<int32> UGGFCharacterDataSubsystem::GetAvailableSkinIDList(const int32 CharacterID)
{
    // 해당 캐릭터가 사용 가능한 스킨 목록 가져오기
    TArray<int32> AvailableSkinIDList = AvailableSkinMap.Contains(CharacterID) ? AvailableSkinMap[CharacterID].List : TArray<int32>();

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
    AvailableSkinIDList.Append(UniversalSkinList);

    return AvailableSkinIDList;
}

#if WITH_EDITOR
FGGFCharacterData* UGGFCharacterDataSubsystem::GetDirectCharacterData(int32 ID)
{
    return static_cast<FGGFCharacterData*>(UGGFDataSubsystem::GetDirectData(UGGFCharacterDefinition::StaticClass(), ID));
}

FGGFCharacterSkinData* UGGFCharacterDataSubsystem::GetDirectCharacterSkinData(int32 ID)
{
    return static_cast<FGGFCharacterSkinData*>(UGGFDataSubsystem::GetDirectData(UGGFCharacterSkinDefinition::StaticClass(), ID));
}
#endif


void UGGFCharacterDataSubsystem::CachingDefinition(UGGFCharacterDefinition* Definition)
{
    // 데이터 에셋 등록
    const int32 CharacterID = Definition->GetID();
    DefinitionList.Emplace(Definition);
    DefinitionMap.Emplace(CharacterID, Definition);
}

void UGGFCharacterDataSubsystem::CachingSkinDefinition(UGGFCharacterSkinDefinition* SkinDefinition)
{
    // 데이터 에셋 등록
    const int32 SkinID = SkinDefinition->GetID();
    SkinDefinitionList.Emplace(SkinDefinition);
    SkinDefinitionMap.Emplace(SkinID, SkinDefinition);

    /* 사용 가능한 캐릭터 매핑 */
    const FGGFCharacterSkinData& Data = SkinDefinition->GetData();

    // 모든 캐릭터가 사용 가능한 경우
    if(Data.AvailableCharacterIDList.IsEmpty())
    {
        UniversalSkinList.Emplace(SkinID);
    }
    else
    {
        // 특정 캐릭터들만 사용 가능한 경우
        for (const int32 CharacterID : Data.AvailableCharacterIDList)
        {
            MappingCharacterSkinID(AvailableSkinMap, CharacterID, SkinID);
        }
    }

    /* 사용 불가능한 캐릭터 매핑 */
    // 특정 캐릭터들만 사용이 불가능한 경우
    for (const int32 CharacterID : Data.ForbiddenCharacterIDList)
    {
        MappingCharacterSkinID(ForbiddenSkinMap, CharacterID, SkinID);
    }
}

void UGGFCharacterDataSubsystem::MappingCharacterSkinID(TMap<int32, FGGFIDContainer>& SkinMap,
    const int32 NewCharacterID, const int32 NewSkinID)
{
    if(SkinMap.Contains(NewCharacterID))
    {
        // 캐릭터 ID가 이미 등록된 경우
        SkinMap[NewCharacterID].List.Emplace(NewSkinID);
    }
    else
    {
        // 처음으로 캐릭터 ID를 등록하는 경우
        FGGFIDContainer NewIDContainer;
        NewIDContainer.List.Emplace(NewSkinID);
        SkinMap.Emplace(NewCharacterID, NewIDContainer);
    }
}
