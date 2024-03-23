// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEAbilityInputTagInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GEGameplayAbilityBase.generated.h"

/**
 * 기본 인스턴스 정책 및 태그가 설정된 기저 Ability입니다.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GASEXTENSION_API UGEGameplayAbilityBase : public UGameplayAbility, public IGEAbilityInputTagInterface
{
    GENERATED_BODY()

    // GEAbilitySystemBase에서 Ability InputID로 사용할 게임플레이 태그입니다.
    UPROPERTY(EditAnywhere, Category = "Config")
    FGameplayTag InputTag;

public:
    UGEGameplayAbilityBase();

    /* AbilityInputTag Interface */

    virtual const FGameplayTag GetInputTag_Implementation() const override;
};
