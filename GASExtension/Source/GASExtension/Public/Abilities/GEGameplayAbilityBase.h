// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GEGameplayAbilityBase.generated.h"

/**
 * 기본 인스턴스 정책 및 태그가 설정된 기저 Ability입니다.
 */
UCLASS(Blueprintable, BlueprintType)
class GASEXTENSION_API UGEGameplayAbilityBase : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UGEGameplayAbilityBase();
};
