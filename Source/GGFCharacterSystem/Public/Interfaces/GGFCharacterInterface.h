// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFCharacterInterface.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class GGFCHARACTERSYSTEM_API UGGFCharacterInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * GASGameFramework 캐릭터 전용 인터페이스
 */
class GGFCHARACTERSYSTEM_API IGGFCharacterInterface
{
    GENERATED_BODY()

public:
    // 캐릭터 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetCharacter(int32 NewCharacterID);

    // 캐릭터 스킨 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetCharacterSkin(int32 NewSkinID);
};
