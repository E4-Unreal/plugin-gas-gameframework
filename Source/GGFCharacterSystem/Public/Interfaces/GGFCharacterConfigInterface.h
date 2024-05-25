// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/GGFCharacterDefinition.h"
#include "GGFCharacterConfigInterface.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class GGFCHARACTERSYSTEM_API UGGFCharacterConfigInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 캐릭터 설정을 위한 인터페이스
 */
class GGFCHARACTERSYSTEM_API IGGFCharacterConfigInterface
{
    GENERATED_BODY()

public:
    // 캐릭터 데이터 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool SetCharacterData(const FGGFCharacterData& NewCharacterData);

    // 캐릭터 데이터 에셋 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool SetCharacterDefinition(UGGFCharacterDefinition* NewDefinition);

    // 캐릭터 ID 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool SetCharacterID(int32 ID);
};
