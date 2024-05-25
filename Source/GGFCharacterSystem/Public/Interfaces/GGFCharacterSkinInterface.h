// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/GGFCharacterSkinDefinition.h"
#include "GGFCharacterSkinInterface.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class GGFCHARACTERSYSTEM_API UGGFCharacterSkinInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 캐릭터 스킨 설정을 위한 인터페이스
 */
class GGFCHARACTERSYSTEM_API IGGFCharacterSkinInterface
{
    GENERATED_BODY()

public:
    // 캐릭터 스킨 데이터 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool SetCharacterSkinData(const FGGFCharacterSkinData& NewCharacterSkinData);

    // 캐릭터 스킨 데이터 에셋 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool SetCharacterSkinDefinition(UGGFCharacterSkinDefinition* NewDefinition);

    // 캐릭터 스킨 ID 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool SetCharacterSkinID(int32 ID);
};
