// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GEBlueprintFunctionLibrary.generated.h"

struct FGameplayCueTag;
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
