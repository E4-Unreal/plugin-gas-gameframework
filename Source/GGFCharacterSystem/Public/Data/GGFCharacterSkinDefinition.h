// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDefinitionBase.h"
#include "GGFCharacterSkinDefinition.generated.h"

// TODO 확장성? 다른 모듈에서 Type 추가 혹은 변경이 가능한지 조사 필요
UENUM(BlueprintType)
enum class EGGFCharacterSkinType : uint8
{
    None,

    Full,
    Head,
    UpperBody,
    LowerBody,
    Hand,
    Foot,

    Max
};

/**
 * 캐릭터 스킨 설정을 위한 구조체
 */
USTRUCT()
struct FGGFCharacterSkinData : public FGGFDataTableRowBase
{
    GENERATED_BODY()

    static const FGGFCharacterSkinData EmptyCharacterSkinData;

    // 스킨 타입
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGGFCharacterSkinType SkinType;

    // 스킨 에셋
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USkeletalMesh> SkeletalMesh;

    // 사용 가능한 캐릭터 ID 목록
    // 비어있는 경우 모든 캐릭터에서 사용 가능한 것으로 취급됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> AvailableCharacterIDList;

    // 사용 불가능한 캐릭터 ID 목록
    // 비어있는 경우 모든 캐릭터에서 사용 가능한 것으로 취급됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> ForbiddenCharacterIDList;

    // 기본 생성자
    FGGFCharacterSkinData() { }
};

/**
 * 캐릭터 스킨 설정을 위한 데이터 에셋
 */
UCLASS()
class GGFCHARACTERSYSTEM_API UGGFCharacterSkinDefinition : public UGGFDefinitionBase
{
    GENERATED_BODY()

protected:
    // 캐릭터 스킨 설정을 위한 데이터
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetData, Category = "Config")
    FGGFCharacterSkinData Data;

public:
    /* GGFDefinitionBase */

    virtual bool InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase) override;

    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FGGFCharacterSkinData& GetData() const { return Data; }
};
