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
    TMap<int32, TObjectPtr<UGGFCharacterDefinition>> CharacterMap;

    // 캐릭터 스킨 데이터 에셋 목록
    UPROPERTY(Transient)
    TArray<TObjectPtr<UGGFCharacterSkinDefinition>> SkinList;

    // 캐릭터 스킨 데이터 에셋의 ID 매핑 정보
    UPROPERTY(Transient)
    TMap<int32, TObjectPtr<UGGFCharacterSkinDefinition>> SkinMap;

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

    // 데이터 테이블로부터 직접 데이터를 읽어오는 메서드로 런타임이 아닌 상황에서 사용합니다.
    UFUNCTION(BlueprintPure, Category = "Character")
    static const FGGFCharacterData& GetData(int32 ID);

    // 모든 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Character")
    const FORCEINLINE TArray<UGGFCharacterDefinition*>& GetAllDefinitions() const { return CharacterList; }

    // ID에 대응하는 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Character")
    FORCEINLINE UGGFCharacterDefinition* GetDefinition(int32 ID) const { return CharacterMap.Contains(ID) ? CharacterMap[ID] : nullptr; }

    // 데이터 테이블로부터 직접 데이터를 읽어오는 메서드로 런타임이 아닌 상황에서 사용합니다.
    UFUNCTION(BlueprintPure, Category = "Skin")
    static const FGGFCharacterSkinData& GetSkinData(int32 ID);

    // 캐릭터 스킨 ID에 대응하는 캐릭터 스킨 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Skin")
    FORCEINLINE UGGFCharacterSkinDefinition* GetSkinDefinition(int32 ID) const { return SkinMap.Contains(ID) ? SkinMap[ID] : nullptr; }

    // 모든 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Skin")
    const FORCEINLINE TArray<UGGFCharacterSkinDefinition*>& GetAllSkinDefinitions() const { return SkinList; }

    // 특정 캐릭터가 사용 가능한 모든 스킨 ID 목록 가져오기
    UFUNCTION(BlueprintPure, Category = "Skin")
    TArray<int32> GetAvailableSkinIDList(const int32 CharacterID) const { return AvailableSkinMap.Contains(CharacterID) ? AvailableSkinMap[CharacterID].List : TArray<int32>(); }

protected:
    // 데이터 서브 시스템 동기화
    virtual void FetchDataSubsystem();

    // 모든 캐릭터 스킨 데이터 분석 및 캐싱
    virtual void CachingSkinList();

    // 특정 캐릭터가 착용 가능한 모든 스킨 ID 매핑
    virtual void MappingAvailableSkin();
};
