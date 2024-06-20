// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDefinitionBase.h"
#include "GGFSkillDefinition.generated.h"

/**
 * 스킬 정의를 위한 데이터 테이블 구조체
 */
USTRUCT()
struct GGFSKILLSYSTEM_API FGGFSkillData : public FGGFDataTableRowBase
{
    GENERATED_BODY()

    // 생성자
    FGGFSkillData() { }

    static const FGGFSkillData EmptyData;
};

/**
 * 스킬 정의를 위한 데이터 에셋
 */
UCLASS()
class GGFSKILLSYSTEM_API UGGFSkillDefinition : public UGGFDefinitionBase
{
    GENERATED_BODY()

protected:
    // 스킬 정의를 위한 데이터
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetData, Category = "Config")
    FGGFSkillData Data;

public:
    /* GGFDefinitionBase */

    virtual bool InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase) override;

    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FGGFSkillData& GetData() const { return Data; }
};
