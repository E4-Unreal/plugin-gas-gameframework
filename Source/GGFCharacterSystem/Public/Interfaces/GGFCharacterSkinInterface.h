// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFCharacterSkinInterface.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class GGFCHARACTERSYSTEM_API UGGFCharacterSkinInterface : public UInterface
{
    GENERATED_BODY()
};

// TODO 부위별 스킨
/**
 * 캐릭터 스킨을 변경하기 위한 인터페이스입니다.
 * 현재는 풀 스킨만 변경이 가능합니다.
 */
class GGFCHARACTERSYSTEM_API IGGFCharacterSkinInterface
{
    GENERATED_BODY()

public:
    // 캐릭터 풀 스킨 변경
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool SetFullSkin(USkeletalMesh* FullSkin);
};
