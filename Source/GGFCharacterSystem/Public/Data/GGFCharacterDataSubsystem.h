// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GGFDataTypes.h"
#include "GGFCharacterDataSubsystem.generated.h"

class UGGFDefinitionBase;
struct FGGFCharacterSkinData;
struct FGGFCharacterData;
class UGGFCharacterDefinition;
class UGGFCharacterSkinDefinition;

/**
 * 캐릭터 데이터 전용 서브 시스템
 */
UCLASS()
class GGFCHARACTERSYSTEM_API UGGFCharacterDataSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

protected:
    // 캐릭터 데이터 에셋 목록
    UPROPERTY(Transient)
    TArray<TObjectPtr<UGGFCharacterDefinition>> CharacterList;

    // 캐릭터 데이터 에셋의 ID 매핑 정보
    UPROPERTY(Transient)
    TMap<int32, TObjectPtr<UGGFCharacterDefinition>> CharacterIDMap;

    // 캐릭터 스킨 데이터 에셋 목록
    UPROPERTY(Transient)
    TArray<TObjectPtr<UGGFCharacterSkinDefinition>> SkinList;

    // 캐릭터 스킨 데이터 에셋의 ID 매핑 정보
    UPROPERTY(Transient)
    TMap<int32, TObjectPtr<UGGFCharacterSkinDefinition>> SkinIDMap;

    // 특정 캐릭터만 착용 가능한 스킨 매핑 정보
    UPROPERTY(Transient)
    FGGFIDMapContainer UniqueSkinMap;

    // 특정 캐릭터만 착용이 불가능한 스킨 매핑 정보
    UPROPERTY(Transient)
    FGGFIDMapContainer ForbiddenSkinMap;

    // 모든 캐릭터가 착용 가능한 스킨 리스트
    UPROPERTY(Transient)
    TArray<int32> UniversalSkinList;

    // 특정 캐릭터가 착용 가능한 모든 스킨 매핑 정보
    // Unique + (Universal - Forbidden)
    UPROPERTY(Transient)
    FGGFIDMapContainer AvailableSkinMap;

public:
    /* Subsystem */

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /* API */

    // 캐릭터 ID에 대응하는 캐릭터 정의 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Character")
    FORCEINLINE UGGFCharacterDefinition* GetDefinition(int32 ID) const { return CharacterIDMap.Contains(ID) ? CharacterIDMap[ID] : nullptr; }

    // 모든 캐릭터 정의 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Character")
    const FORCEINLINE TArray<UGGFCharacterDefinition*>& GetAllDefinitions() const { return CharacterList; }

    // 캐릭터 스킨 ID에 대응하는 캐릭터 스킨 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Skin")
    FORCEINLINE UGGFCharacterSkinDefinition* GetSkinDefinition(int32 ID) const { return SkinIDMap.Contains(ID) ? SkinIDMap[ID] : nullptr; }

    // 모든 캐릭터 스킨 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Skin")
    const FORCEINLINE TArray<UGGFCharacterSkinDefinition*>& GetAllSkinDefinitions() const { return SkinList; }

    // 특정 캐릭터가 사용 가능한 모든 스킨 ID 목록 가져오기
    UFUNCTION(BlueprintPure, Category = "Skin")
    TArray<int32> GetAvailableSkinIDList(const int32 CharacterID) const { return AvailableSkinMap.Contains(CharacterID) ? AvailableSkinMap[CharacterID].List : TArray<int32>(); }

#if WITH_EDITOR
    // 데이터 테이블로부터 CharacterData 가져오기
    static const FGGFCharacterData* GetDirectCharacterData(int32 ID);

    // 데이터 테이블로부터 모든 CharacterData 가져오기
    static const TArray<const FGGFCharacterData*> GetAllDirectCharacterData();

    // 데이터 테이블로부터 CharacterSkinData 직접 가져오기
    static const FGGFCharacterSkinData* GetDirectCharacterSkinData(int32 ID);

    // 데이터 테이블로부터 CharacterSkinData 직접 가져오기
    static const TArray<const FGGFCharacterSkinData*> GetAllDirectCharacterSkinData();
#endif

protected:
    /* Character */

    // 모든 캐릭터 데이터 등록
    virtual void CachingAllCharacters();

    /* Skin */

    // 모든 캐릭터 스킨 데이터 등록
    virtual void CachingAllSkins();

    // 등록된 모든 캐릭터 스킨 데이터 분석
    virtual void AnalyzeAllSkins();

    // 주어진 캐릭터가 착용 가능한 모든 스킨 ID 캐싱
    virtual void RegisterAvailableSkin(int32 CharacterID);
};
