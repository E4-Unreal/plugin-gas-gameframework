// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "GGFInputConfig.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FGGFInputWithGameplayTag
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UInputAction* InputAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag InputTag;
};

/**
 * GGFAbilitySystemBase에서 InputTag 바인딩을 위해 사용하는 데이터 에셋입니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGGFInputConfig : public UDataAsset
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Config")
    TArray<FGGFInputWithGameplayTag> InputWithGameplayTagList;

public:
    UFUNCTION(BlueprintPure)
    const TArray<FGGFInputWithGameplayTag>& GetInputWithGameplayTagList() const { return InputWithGameplayTagList; }
};
