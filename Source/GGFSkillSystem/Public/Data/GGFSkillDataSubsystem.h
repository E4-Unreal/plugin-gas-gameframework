// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GGFSkillDataSubsystem.generated.h"

struct FGGFSkillData;
class UGGFSkillDefinition;

/**
 * 스킬 전용 데이터 서브 시스템
 */
UCLASS()
class GGFSKILLSYSTEM_API UGGFSkillDataSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

protected:
    // 데이터 에셋 목록
    UPROPERTY(Transient)
    TArray<TObjectPtr<UGGFSkillDefinition>> SkillList;

    // 데이터 에셋의 ID 매핑 정보
    UPROPERTY(Transient)
    TMap<int32, TObjectPtr<UGGFSkillDefinition>> SkillMap;

public:
    /* Subsystem */

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /* API */

    // 데이터 테이블로부터 직접 데이터를 읽어오는 메서드로 런타임이 아닌 상황에서 사용합니다.
    UFUNCTION(BlueprintPure, Category = "Skill")
    static const FGGFSkillData& GetData(int32 ID);

    // 모든 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Skill")
    const FORCEINLINE TArray<UGGFSkillDefinition*>& GetAllDefinitions() const { return SkillList; }

    // ID에 대응하는 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Skill")
    FORCEINLINE UGGFSkillDefinition* GetDefinition(int32 ID) const { return SkillMap.Contains(ID) ? SkillMap[ID] : nullptr; }

protected:
    // 데이터 서브 시스템 동기화
    virtual void FetchDataSubsystem();
};
