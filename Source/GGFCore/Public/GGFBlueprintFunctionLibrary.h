// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GGFBlueprintFunctionLibrary.generated.h"

struct FGameplayAbilitySpecHandle;
struct FGameplayEffectSpec;
struct FActiveGameplayEffectHandle;
class UGameplayEffect;
class UAttributeSet;
class UGameplayAbility;
class UAbilitySystemComponent;

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

        /* Create And Add AttributeSet To Actor */

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|AttributeSet|Actor")
    static void AddAttributeSetToTarget(const TSubclassOf<UAttributeSet> AttributeSetClass, const AActor* TargetActor);

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|AttributeSet|Actor")
    static void AddAttributeSetsToTarget(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses, const AActor* TargetActor);

    /* Create And Add AttributeSet To AbilitySystem */

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|AttributeSet|System")
    static void AddAttributeSetToSystem(const TSubclassOf<UAttributeSet> AttributeSetClass, UAbilitySystemComponent* AbilitySystem);

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|AttributeSet|System")
    static void AddAttributeSetsToSystem(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses, UAbilitySystemComponent* AbilitySystem);

    /* Give GameplayAbility To Actor */

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|GameplayAbility|Actor")
    static FGameplayAbilitySpecHandle GiveAbilityToTarget(const TSubclassOf<UGameplayAbility> AbilityClass, const AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|GameplayAbility|Actor")
    static TArray<FGameplayAbilitySpecHandle> GiveAbilitiesToTarget(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses, const AActor* Target);

    /* Give GameplayAbility To AbilitySystem */

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|GameplayAbility|System")
    static FGameplayAbilitySpecHandle GiveAbilityToSystem(const TSubclassOf<UGameplayAbility> AbilityClass, UAbilitySystemComponent* AbilitySystem);

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|GameplayAbility|System")
    static TArray<FGameplayAbilitySpecHandle> GiveAbilitiesToSystem(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses, UAbilitySystemComponent* AbilitySystem);

    /* 데미지 */

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|Damage")
    static void ApplyDamageToSelf(AActor* Target, TSubclassOf<UGameplayEffect> DamageClass, float Damage = 0, float DamageRatio = 1, FGameplayTag DamageTypeTag = FGameplayTag());

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|Damage")
    static void ApplyDamageToTarget(AActor* Source, AActor* Target, TSubclassOf<UGameplayEffect> DamageClass, float Damage = 0, float DamageRatio = 1, FGameplayTag DamageTypeTag = FGameplayTag());

    /* 게임플레이 큐 */

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|GameplayCue")
    static void LocalHandleGameplayCue(AActor* EffectCauser, const FGameplayCueTag& CueTag, AActor* Target = nullptr, AActor* Instigator = nullptr);

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|GameplayCue")
    static void LocalHandleGameplayCueWithTransform(AActor* EffectCauser, const FGameplayCueTag& CueTag, const FTransform& Transform, AActor* Target = nullptr, AActor* Instigator = nullptr);
};
