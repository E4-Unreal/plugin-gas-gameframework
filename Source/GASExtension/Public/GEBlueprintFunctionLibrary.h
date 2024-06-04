// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GEBlueprintFunctionLibrary.generated.h"

class UGameplayEffect;
struct FGameplayAbilitySpecHandle;
struct FActiveGameplayEffectHandle;

/**
 * GASExtension 모듈에서 사용하는 블루프린트 함수 라이브러리입니다.
 */
UCLASS()
class GASEXTENSION_API UGEBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
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

    /* Apply GameplayEffect To Actor */

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|GameplayEffect|Actor")
    static FActiveGameplayEffectHandle ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* TargetActor);

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|GameplayEffect|Actor")
    static TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectsToSelf(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, const AActor* TargetActor);

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|GameplayEffect|Actor")
    static FActiveGameplayEffectHandle ApplyGameplayEffectToTarget(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* Instigator, const AActor* TargetActor);

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|GameplayEffect|Actor")
    static TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectsToTarget(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, const AActor* Instigator, const AActor* TargetActor);

    /* Apply GameplayEffect To AbilitySystem */

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|GameplayEffect|System")
    static FActiveGameplayEffectHandle ApplyGameplayEffectToSystem(const TSubclassOf<UGameplayEffect> EffectClass, UAbilitySystemComponent* AbilitySystem);

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|GameplayEffect|System")
    static TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectsToSystem(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, UAbilitySystemComponent* AbilitySystem);

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|GameplayEffect|System")
    static FActiveGameplayEffectHandle ApplyGameplayEffectToTargetSystem(const TSubclassOf<UGameplayEffect> EffectClass, UAbilitySystemComponent* InstigatorAbilitySystem, UAbilitySystemComponent* TargetAbilitySystem);

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|GameplayEffect|System")
    static TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectsToTargetSystem(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, UAbilitySystemComponent* Instigator, UAbilitySystemComponent* TargetAbilitySystem);

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

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|Damage")
    static void ApplyRadialDamageToSelf(AActor* Target, AActor* ExplosiveActor, TSubclassOf<UGameplayEffect> DamageClass, float Damage = 0, FGameplayTag DamageTypeTag = FGameplayTag(), float InnerRadius = 200, ECollisionChannel CollisionChannel = ECC_WorldDynamic, bool bShowDebug = false);

    UFUNCTION(BlueprintCallable, Category = "GEBlueprintFunctionLibrary|Damage")
    static void ApplyRadialDamageToTarget(AActor* Source, AActor* Target, AActor* ExplosiveActor, TSubclassOf<UGameplayEffect> DamageClass, float Damage = 0, FGameplayTag DamageTypeTag = FGameplayTag(), float InnerRadius = 200, ECollisionChannel CollisionChannel = ECC_WorldDynamic, bool bShowDebug = false);

protected:
    // TODO 리팩토링, 액터 컴포넌트?
    // ApplyRadialDamage를 위한 데미지 배율 계산
    static float CalculateDamageRatioForExplosion(AActor* Target, AActor* ExplosiveActor, float InnerRadius = 200, ECollisionChannel CollisionChannel = ECC_WorldDynamic, bool bShowDebug = false);

    // TODO 피격판정 수정 필요
    // 폭발 피격 판정을 위한 위치 계산
    static void GetLocationsForExplosionDetection(AActor* Target, TArray<FVector>& TargetLocations);
};
