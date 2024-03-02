// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GEFunctionLibrary.generated.h"

/**
 * GASExtension 플러그인에서 사용하는 함수 라이브러리입니다.
 */
UCLASS()
class GASEXTENSION_API UGEFunctionLibrary : public UObject
{
    GENERATED_BODY()

public:
    static void ApplyGameplayEffectToTarget(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* Instigator, const AActor* Target);
    static void ApplyGameplayEffectsToTarget(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, const AActor* Instigator, const AActor* Target);

    static void ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* Target);
    static void ApplyGameplayEffectsToSelf(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, const AActor* Target);
};
