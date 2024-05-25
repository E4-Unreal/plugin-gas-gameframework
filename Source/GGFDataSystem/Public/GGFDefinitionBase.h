// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "GGFDefinitionBase.generated.h"

/**
 * 데이터 시스템에서 사용되는 기본 데이터 테이블 구조체로
 * 데이터 유효성 검사를 위한 가상 메서드가 정의되어 있습니다.
 */
USTRUCT(Atomic, BlueprintType)
struct FGGFDataTableRowBase : public FTableRowBase
{
    GENERATED_BODY()

    // 표시명
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = -1))
    FName DisplayName;

    virtual FORCEINLINE bool IsValid() const { return true; }
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }
};

/**
 * 데이터 시스템에서 사용되는 기본 데이터 에셋 클래스로
 * 데이터 테이블로부터 초기화를 위한 가상 메서드가 정의되어 있습니다.
 */
UCLASS(BlueprintType, Blueprintable, HideDropdown, EditInlineNew)
class GGFDATASYSTEM_API UGGFDefinitionBase : public UDataAsset
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, Category = "State", Transient)
    TObjectPtr<UDataTable> DataTable;

    UPROPERTY(VisibleAnywhere, Category = "State", Transient)
    bool bValid = true;

protected:
    UPROPERTY(EditAnywhere, BlueprintGetter = GetID, Category = "Config", meta = (ClampMin = 0, DisplayPriority = -1))
    int32 ID;

public:
    /* API */

    // 데이터 테이블로부터 데이터 에셋을 초기화하기 위한 메서드
    UFUNCTION(BlueprintCallable)
    bool InitFromDataTable(UDataTable* NewDataTable, int32 NewID);

    UFUNCTION(BlueprintPure)
    virtual FORCEINLINE bool IsValid() const { return bValid; }

    UFUNCTION(BlueprintPure)
    bool IsNotValid() const { return !IsValid(); }

protected:
    /* 메서드 */

    // 데이터 테이블 구조체를 이용하여 데이터 에셋 초기화 진행
    virtual bool InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase);

public:
    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetID() const { return ID; }
};
