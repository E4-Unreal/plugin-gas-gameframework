// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "GGFInputConfig.generated.h"

/**
 * 입력 액션과 게임플레이 입력 태그 매핑을 위한 구조체
 */
USTRUCT(Atomic, BlueprintType)
struct FGGFInputAction
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UInputAction* InputAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Input"))
    FGameplayTag InputTag;
};

/**
 * 어빌리티 전용 입력 액션과 게임플레이 입력 태그 매핑 정보를 저장하는 데이터 에셋
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGGFInputConfig : public UDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    TArray<FGGFInputAction> AbilityInputActions;

public:
    UFUNCTION(BlueprintPure)
    const TArray<FGGFInputAction>& GetAbilityInputActions() const { return AbilityInputActions; }
};
