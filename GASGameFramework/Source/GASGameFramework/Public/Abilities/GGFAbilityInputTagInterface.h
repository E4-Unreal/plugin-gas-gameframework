// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTags.h"
#include "GGFAbilityInputTagInterface.generated.h"

UINTERFACE(Blueprintable, BlueprintType)
class UGGFAbilityInputTagInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * GGFAbilitySystemBase에서 Ability InputID를 설정하기 위한 입력 태그를 반환합니다.
 */
class GASGAMEFRAMEWORK_API IGGFAbilityInputTagInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    const FGameplayTag GetInputTag() const;
};
