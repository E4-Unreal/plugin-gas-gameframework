﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "GEPlayerAbilityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, Blueprintable)
class GASEXTENSION_API UGEPlayerAbilityInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 플레이어 입력 바인딩을 위해 게임플레이 어빌리티에서 설정된 입력 태그를 가져오기 위한 인터페이스
 */
class GASEXTENSION_API IGEPlayerAbilityInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FGameplayTag GetAbilityInputTag() const;
};
