// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GEBlueprintFunctionLibrary.generated.h"

class UGameplayEffect;
/**
 * GASExtension 플러그인에서 사용하는 블루프린트 함수 라이브러리입니다.
 */
UCLASS()
class GASEXTENSION_API UGEBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "GASExtension")
    static void ApplyGameplayEffectToTarget(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* Instigator, const AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "GASExtension")
    static void ApplyGameplayEffectsToTarget(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, const AActor* Instigator, const AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "GASExtension")
    static void ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "GASExtension")
    static void ApplyGameplayEffectsToSelf(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, const AActor* Target);
};
