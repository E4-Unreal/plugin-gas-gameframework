// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GEInputConfig.h"
#include "GEInputConfig_Ability.generated.h"

/**
 * 어빌리티 입력 액션과 입력 태그 매핑을 위한 구조체
 */
USTRUCT(Atomic, BlueprintType)
struct FGGFAbilityInputAction
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UInputAction* InputAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Input"))
    FGameplayTag InputTag;
};

/**
 * 어빌리티 전용 입력 에셋 설정을 위한 데이터 에셋으로 GGFAbilitySystemBase에 의존성을 가지고 있습니다.
 */
UCLASS()
class GASEXTENSION_API UGEInputConfig_Ability : public UGEInputConfig
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly)
    TArray<FGGFAbilityInputAction> AbilityInputActions;

protected:
    virtual void OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent) override;
};
