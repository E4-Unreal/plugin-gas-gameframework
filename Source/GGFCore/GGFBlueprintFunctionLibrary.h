// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GGFBlueprintFunctionLibrary.generated.h"

struct FGameplayEffectSpec;
struct FActiveGameplayEffectHandle;
class UGameplayEffect;

/**
 * GASGameFramework 플러그인 전용 블루프린트 함수 라이브러리
 */
UCLASS()
class GGFCORE_API UGGFBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /* GameplayEffectSpec */

    UFUNCTION(BlueprintCallable, Category = "GGFBlueprintFunctionLibrary|GameplayEffect")
    static FActiveGameplayEffectHandle ApplyGameplayEffectSpecToSelf(const AActor* TargetActor, const FGameplayEffectSpec& EffectSpec);

    UFUNCTION(BlueprintCallable, Category = "GGFBlueprintFunctionLibrary|GameplayEffect")
    static TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectSpecsToSelf(const AActor* TargetActor, const TArray<FGameplayEffectSpec>& EffectSpecs);

    UFUNCTION(BlueprintCallable, Category = "GGFBlueprintFunctionLibrary|GameplayEffect")
    static FActiveGameplayEffectHandle ApplyGameplayEffectSpecToTarget(const AActor* InstigatorActor, const AActor* TargetActor, const FGameplayEffectSpec& EffectSpec);

    UFUNCTION(BlueprintCallable, Category = "GGFBlueprintFunctionLibrary|GameplayEffect")
    static TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectSpecsToTarget(const AActor* InstigatorActor, const AActor* TargetActor, const TArray<FGameplayEffectSpec>& EffectSpecs);

    /* GameplayEffect */

    UFUNCTION(BlueprintCallable, Category = "GGFBlueprintFunctionLibrary|GameplayEffect")
    static FActiveGameplayEffectHandle ApplyGameplayEffectToSelf(const AActor* TargetActor, const TSubclassOf<UGameplayEffect> EffectClass);

    UFUNCTION(BlueprintCallable, Category = "GGFBlueprintFunctionLibrary|GameplayEffect")
    static TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectsToSelf(const AActor* TargetActor, const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses);

    UFUNCTION(BlueprintCallable, Category = "GGFBlueprintFunctionLibrary|GameplayEffect")
    static FActiveGameplayEffectHandle ApplyGameplayEffectToTarget(const AActor* InstigatorActor, const AActor* TargetActor, const TSubclassOf<UGameplayEffect> EffectClass);

    UFUNCTION(BlueprintCallable, Category = "GGFBlueprintFunctionLibrary|GameplayEffect")
    static TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectsToTarget(const AActor* InstigatorActor, const AActor* TargetActor, const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses);
};
