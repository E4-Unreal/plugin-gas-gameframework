// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDefinitionBase.h"
#include "GGFSkillDefinition.generated.h"

class UGameplayAbility;

/**
 * 스킬 정의를 위한 데이터 테이블 구조체
 */
USTRUCT()
struct GGFSKILLSYSTEM_API FGGFSkillData : public FGGFDataTableRowBase
{
    GENERATED_BODY()

    // 설명
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spec")
    FText Description;

    // 쿨타임
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spec")
    float CoolTime = 3;

    // 어빌리티 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spec")
    TSubclassOf<UGameplayAbility> AbilityClass;

    // 썸네일
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TObjectPtr<UTexture2D> Thumbnail;

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
    virtual bool IsValid() const override;

    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FGGFSkillData& GetData() const { return Data; }
};
