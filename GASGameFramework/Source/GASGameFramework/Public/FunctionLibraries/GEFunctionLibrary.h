// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GGFFunctionLibrary.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
struct FGameplayAbilitySpecHandle;

/**
 * GASExtension 플러그인에서 사용하는 함수 라이브러리입니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGGFFunctionLibrary : public UObject
{
    GENERATED_BODY()

public:
    /* Create And Add AttributeSet To Actor */

    static void AddAttributeSetToTarget(const TSubclassOf<UAttributeSet> AttributeSetClass, const AActor* TargetActor);

    static void AddAttributeSetsToTarget(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses, const AActor* TargetActor);

    /* Create And Add AttributeSet To AbilitySystem */

    static void AddAttributeSetToSystem(const TSubclassOf<UAttributeSet> AttributeSetClass, UAbilitySystemComponent* AbilitySystem);

    static void AddAttributeSetsToSystem(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses, UAbilitySystemComponent* AbilitySystem);

    /* Apply GameplayEffect To Actor */

    // 내부적으로 ApplyGameplayEffectToSystem을 호출하며 Actor를 AbilitySystemComponent로 변환 기능만 추가하였습니다.
    static void ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* TargetActor);

    // 내부적으로 ApplyGameplayEffectsToSystem을 호출하며 Actor를 AbilitySystemComponent로 변환 기능만 추가하였습니다.
    static void ApplyGameplayEffectsToSelf(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, const AActor* TargetActor);

    // 내부적으로 ApplyGameplayEffectToTargetSystem을 호출하며 Actor를 AbilitySystemComponent로 변환 기능만 추가하였습니다.
    static void ApplyGameplayEffectToTarget(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* Instigator, const AActor* TargetActor);

    // 내부적으로 ApplyGameplayEffectsToTargetSystem을 호출하며 Actor를 AbilitySystemComponent로 변환 기능만 추가하였습니다.
    static void ApplyGameplayEffectsToTarget(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, const AActor* Instigator, const AActor* TargetActor);

    /* Apply GameplayEffect To AbilitySystem */

    static void ApplyGameplayEffectToSystem(const TSubclassOf<UGameplayEffect> EffectClass, UAbilitySystemComponent* AbilitySystem);

    static void ApplyGameplayEffectsToSystem(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, UAbilitySystemComponent* AbilitySystem);

    static void ApplyGameplayEffectToTargetSystem(const TSubclassOf<UGameplayEffect> EffectClass, UAbilitySystemComponent* Instigator, UAbilitySystemComponent* TargetAbilitySystem);

    static void ApplyGameplayEffectsToTargetSystem(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, UAbilitySystemComponent* Instigator, UAbilitySystemComponent* TargetAbilitySystem);

    /* Give GameplayAbility To Actor */

    static FGameplayAbilitySpecHandle GiveAbilityToTarget(const TSubclassOf<UGameplayAbility> AbilityClass, const AActor* Target);

    static TArray<FGameplayAbilitySpecHandle> GiveAbilitiesToTarget(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses, const AActor* Target);

    /* Give GameplayAbility To AbilitySystem */

    static FGameplayAbilitySpecHandle GiveAbilityToSystem(const TSubclassOf<UGameplayAbility> AbilityClass, UAbilitySystemComponent* AbilitySystem);

    static TArray<FGameplayAbilitySpecHandle> GiveAbilitiesToSystem(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses, UAbilitySystemComponent* AbilitySystem);
};
