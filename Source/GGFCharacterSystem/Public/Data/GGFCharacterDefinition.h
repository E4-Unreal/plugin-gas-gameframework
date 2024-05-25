// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "GGFCharacterDefinition.generated.h"

/**
 * 캐릭터 정의를 위한 데이터 테이블
 */
USTRUCT(BlueprintType)
struct FGGFCharacterDataTableRow : public FTableRowBase
{
    GENERATED_BODY()

    // 기본 스켈레탈 메시
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USkeletalMesh> SkeletalMesh;

    // 기본 애니메이션
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UAnimInstance> AnimInstanceClass;
};

/**
 * 캐릭터 정의를 위한 구조체
 */
USTRUCT(Atomic, BlueprintType)
struct FGGFCharacterData
{
    GENERATED_BODY()

    // 캐릭터 ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
    int32 ID;

    // 기본 스켈레탈 메시
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USkeletalMesh> SkeletalMesh;

    // 기본 애니메이션
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UAnimInstance> AnimInstanceClass;

    /* 대입 연산자 오버로딩 */

    FGGFCharacterData& operator=(const FGGFCharacterDataTableRow& DataTableRow)
    {
        SkeletalMesh = DataTableRow.SkeletalMesh;
        AnimInstanceClass = DataTableRow.AnimInstanceClass;

        return *this;
    }
};

/**
 * 캐릭터 정의를 위한 데이터 에셋
 */
UCLASS(BlueprintType, Blueprintable)
class GGFCHARACTERSYSTEM_API UGGFCharacterDefinition : public UDataAsset
{
    GENERATED_BODY()

protected:
    // 캐릭터 정의를 위한 데이터
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetData, Category = "Config")
    FGGFCharacterData Data;

public:
    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void InitFromDataTable(UDataTable* DataTable, int32 ID);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FGGFCharacterData& GetData() const { return Data; }
};
