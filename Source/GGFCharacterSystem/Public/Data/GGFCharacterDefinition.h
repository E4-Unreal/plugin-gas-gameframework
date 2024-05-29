// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDefinitionBase.h"
#include "GGFCharacterDefinition.generated.h"

/**
 * 캐릭터 정의를 위한 데이터 테이블 구조체
 */
USTRUCT()
struct FGGFCharacterData : public FGGFDataTableRowBase
{
    GENERATED_BODY()

    // 캐릭터 썸네일
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UTexture2D> Thumbnail;

    // 기본 스켈레탈 메시
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USkeletalMesh> SkeletalMesh;

    // 기본 애니메이션
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UAnimInstance> AnimInstanceClass;
};

/**
 * 캐릭터 정의를 위한 데이터 에셋
 */
UCLASS(BlueprintType, Blueprintable)
class GGFCHARACTERSYSTEM_API UGGFCharacterDefinition : public UGGFDefinitionBase
{
    GENERATED_BODY()

protected:
    // 캐릭터 정의를 위한 데이터
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetData, Category = "Config")
    FGGFCharacterData Data;

public:
    /* GGFDefinitionBase */

    virtual bool InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase) override;

    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FGGFCharacterData& GetData() const { return Data; }
};
