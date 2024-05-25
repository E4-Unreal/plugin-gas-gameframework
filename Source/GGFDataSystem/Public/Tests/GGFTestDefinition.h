// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDefinitionBase.h"
#include "GGFTestDefinition.generated.h"

/**
 * 테스트 전용 데이터 테이블 구조체
 */
USTRUCT(Atomic, BlueprintType)
struct FTestDataTableRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName TestName;
};

/**
 * 테스트 전용 데이터 에셋
 */
UCLASS()
class GGFDATASYSTEM_API UGGFTestDefinition : public UGGFDefinitionBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetData, Category = "Config")
    FTestDataTableRow Data;

public:
    /* GGFDefinitionBase */

    virtual bool Internal_InitFromDataTable_Implementation() override;

    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FTestDataTableRow& GetData() const { return Data; }
};
