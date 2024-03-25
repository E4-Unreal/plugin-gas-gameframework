// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTags.h"
#include "GEAbilityInputTagInterface.generated.h"

UINTERFACE(Blueprintable, BlueprintType)
class UGEAbilityInputTagInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * GEAbilitySystemBase에서 Ability InputID를 설정하기 위한 입력 태그를 반환합니다.
 */
class GASGAMEFRAMEWORK_API IGEAbilityInputTagInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    const FGameplayTag GetInputTag() const;
};
