// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GGFDefinitionBase.generated.h"

/**
 * 데이터 시스템에서 사용되는 기본 데이터 에셋 클래스로 데이터 테이블로부터 초기화를 위한 가상 메서드가 정의되어 있습니다.
 */
UCLASS(BlueprintType, Blueprintable)
class GGFDATASYSTEM_API UGGFDefinitionBase : public UDataAsset
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, Category = "State", Transient)
    TObjectPtr<UDataTable> DataTable;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
    int32 ID;

public:
    /* API */

    UFUNCTION(BlueprintCallable)
    void InitFromDataTable(UDataTable* NewDataTable, int32 NewID);

protected:
    /* 메서드 */

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Internal_InitFromDataTable();
};
