// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GGFDataTypes.h"
#include "GGFCharacterDataSubsystem.generated.h"

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
    // 캐릭터 정의 데이터 에셋 목록
    UPROPERTY(Transient)
    TArray<TObjectPtr<UGGFCharacterDefinition>> DefinitionList;

    // 캐릭터 스킨 데이터 에셋 목록
    UPROPERTY(Transient)
    TArray<TObjectPtr<UGGFCharacterSkinDefinition>> SkinDefinitionList;

    // 캐릭터 정의 데이터 에셋의 ID 매핑 정보
    UPROPERTY(Transient)
    TMap<int32, TObjectPtr<UGGFCharacterDefinition>> DefinitionMap;

    // 캐릭터 스킨 데이터 에셋의 ID 매핑 정보
    UPROPERTY(Transient)
    TMap<int32, TObjectPtr<UGGFCharacterSkinDefinition>> SkinDefinitionMap;

    // 캐릭터 별 착용 가능한 스킨 매핑 정보
    UPROPERTY(Transient)
    TMap<int32, FGGFIDContainer> AvailableSkinMap;

    // 캐릭터 별 착용이 불가능한 스킨 매핑 정보
    UPROPERTY(Transient)
    TMap<int32, FGGFIDContainer> ForbiddenSkinMap;

    // 모든 캐릭터가 착용 가능한 스킨 리스트
    UPROPERTY(Transient)
    TArray<int32> UniversalSkinList;

public:
    /* Subsystem */

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /* API */

    UFUNCTION(BlueprintPure, Category = "Character")
    FORCEINLINE UGGFCharacterDefinition* GetDefinition(int32 ID) const { return DefinitionMap.Contains(ID) ? DefinitionMap[ID] : nullptr; }

    UFUNCTION(BlueprintPure, Category = "Character")
    const FORCEINLINE TArray<UGGFCharacterDefinition*>& GetAllDefinitions() const { return DefinitionList; }

    UFUNCTION(BlueprintPure, Category = "Skin")
    FORCEINLINE UGGFCharacterSkinDefinition* GetSkinDefinition(int32 ID) const { return SkinDefinitionMap.Contains(ID) ? SkinDefinitionMap[ID] : nullptr; }

    UFUNCTION(BlueprintPure, Category = "Skin")
    const FORCEINLINE TArray<UGGFCharacterSkinDefinition*>& GetAllSkinDefinitions() const { return SkinDefinitionList; }

    // 특정 캐릭터가 사용 가능한 모든 스킨 ID 목록 가져오기
    UFUNCTION(BlueprintPure, Category = "Skin")
    TArray<int32> GetAllAvailableSkinIDList(const int32 CharacterID);

#if WITH_EDITOR
    // 데이터 테이블로부터 CharacterData 직접 가져오기
    static FGGFCharacterData* GetDirectCharacterData(int32 ID);

    // 데이터 테이블로부터 CharacterSkinData 직접 가져오기
    static FGGFCharacterSkinData* GetDirectCharacterSkinData(int32 ID);
#endif

protected:
    // 캐릭터 정의 데이터 에셋 캐싱
    virtual void CachingDefinition(UGGFCharacterDefinition* Definition);

    // 캐릭터 스킨 데이터 에셋 캐싱
    virtual void CachingSkinDefinition(UGGFCharacterSkinDefinition* SkinDefinition);

    // 캐릭터 ID와 캐릭터 스킨 ID 매핑
    void MappingCharacterSkinID(TMap<int32, FGGFIDContainer>& SkinMap, const int32 NewCharacterID, const int32 NewSkinID);
};
