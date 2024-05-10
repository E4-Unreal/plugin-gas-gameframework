﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GEBlueprintFunctionLibrary.generated.h"

class UGameplayEffect;
struct FGameplayAbilitySpecHandle;

/**
 * GASExtension 모듈에서 사용하는 블루프린트 함수 라이브러리입니다.
 */
UCLASS()
class GASEXTENSION_API UGEBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /* Create And Add AttributeSet To Actor */

    UFUNCTION(BlueprintCallable, Category = "AttributeSet|Actor")
    static void AddAttributeSetToTarget(const TSubclassOf<UAttributeSet> AttributeSetClass, const AActor* TargetActor);

    UFUNCTION(BlueprintCallable, Category = "AttributeSet|Actor")
    static void AddAttributeSetsToTarget(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses, const AActor* TargetActor);

    /* Create And Add AttributeSet To AbilitySystem */

    UFUNCTION(BlueprintCallable, Category = "AttributeSet|System")
    static void AddAttributeSetToSystem(const TSubclassOf<UAttributeSet> AttributeSetClass, UAbilitySystemComponent* AbilitySystem);

    UFUNCTION(BlueprintCallable, Category = "AttributeSet|System")
    static void AddAttributeSetsToSystem(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses, UAbilitySystemComponent* AbilitySystem);

    /* Apply GameplayEffect To Actor */

    UFUNCTION(BlueprintCallable, Category = "GameplayEffect|Actor")
    static void ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* TargetActor);

    UFUNCTION(BlueprintCallable, Category = "GameplayEffect|Actor")
    static void ApplyGameplayEffectsToSelf(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, const AActor* TargetActor);

    UFUNCTION(BlueprintCallable, Category = "GameplayEffect|Actor")
    static void ApplyGameplayEffectToTarget(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* Instigator, const AActor* TargetActor);

    UFUNCTION(BlueprintCallable, Category = "GameplayEffect|Actor")
    static void ApplyGameplayEffectsToTarget(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, const AActor* Instigator, const AActor* TargetActor);

    /* Apply GameplayEffect To AbilitySystem */

    UFUNCTION(BlueprintCallable, Category = "GameplayEffect|System")
    static void ApplyGameplayEffectToSystem(const TSubclassOf<UGameplayEffect> EffectClass, UAbilitySystemComponent* AbilitySystem);

    UFUNCTION(BlueprintCallable, Category = "GameplayEffect|System")
    static void ApplyGameplayEffectsToSystem(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, UAbilitySystemComponent* AbilitySystem);

    UFUNCTION(BlueprintCallable, Category = "GameplayEffect|System")
    static void ApplyGameplayEffectToTargetSystem(const TSubclassOf<UGameplayEffect> EffectClass, UAbilitySystemComponent* Instigator, UAbilitySystemComponent* TargetAbilitySystem);

    UFUNCTION(BlueprintCallable, Category = "GameplayEffect|System")
    static void ApplyGameplayEffectsToTargetSystem(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, UAbilitySystemComponent* Instigator, UAbilitySystemComponent* TargetAbilitySystem);

    /* Give GameplayAbility To Actor */

    UFUNCTION(BlueprintCallable, Category = "GameplayAbility|Actor")
    static FGameplayAbilitySpecHandle GiveAbilityToTarget(const TSubclassOf<UGameplayAbility> AbilityClass, const AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "GameplayAbility|Actor")
    static TArray<FGameplayAbilitySpecHandle> GiveAbilitiesToTarget(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses, const AActor* Target);

    /* Give GameplayAbility To AbilitySystem */

    UFUNCTION(BlueprintCallable, Category = "GameplayAbility|System")
    static FGameplayAbilitySpecHandle GiveAbilityToSystem(const TSubclassOf<UGameplayAbility> AbilityClass, UAbilitySystemComponent* AbilitySystem);

    UFUNCTION(BlueprintCallable, Category = "GameplayAbility|System")
    static TArray<FGameplayAbilitySpecHandle> GiveAbilitiesToSystem(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses, UAbilitySystemComponent* AbilitySystem);

};