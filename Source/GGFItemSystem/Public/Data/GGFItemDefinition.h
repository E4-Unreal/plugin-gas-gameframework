// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDefinitionBase.h"
#include "Engine/DataAsset.h"
#include "GGFItemDefinition.generated.h"

/**
 * 아이템 정의를 위한 데이터 테이블 구조체
 */
USTRUCT()
struct GGFITEMSYSTEM_API FGGFItemData : public FGGFDataTableRowBase
{
    GENERATED_BODY()

    // 아이템 썸네일
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UTexture2D> Thumbnail;

    // 기본 스태틱 메시
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UStaticMesh> DisplayMesh;

    // 하나의 아이템이 가질 수 있는 최대 수량
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 MaxStack = 1;

    // 기본 아이템 수량
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 Amount = 1;
};

/**
 * 아이템 정의를 위한 데이터 에셋
 */
UCLASS(BlueprintType, Blueprintable)
class GGFITEMSYSTEM_API UGGFItemDefinition : public UGGFDefinitionBase
{
    GENERATED_BODY()

protected:
    // 아이템 정의를 위한 데이터
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetData, Category = "Config")
    FGGFItemData Data;

public:
    /* GGFDefinitionBase */

    virtual bool InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase) override;

    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FGGFItemData& GetData() const { return Data; }
};
