// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameplayEffect.h"

FActiveGameplayEffectHandle UGGFBlueprintFunctionLibrary::ApplyGameplayEffectSpecToSelf(const AActor* TargetActor,
    const FGameplayEffectSpec& EffectSpec)
{
    // 지역 변수 정의
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr) return FActiveGameplayEffectHandle();

    // 게임플레이 이펙트 적용
    return TargetSystem->ApplyGameplayEffectSpecToSelf(EffectSpec);
}

TArray<FActiveGameplayEffectHandle> UGGFBlueprintFunctionLibrary::ApplyGameplayEffectSpecsToSelf(const AActor* TargetActor,
    const TArray<FGameplayEffectSpec>& EffectSpecs)
{
    // 지역 변수 정의
    TArray<FActiveGameplayEffectHandle> Results;
    Results.Reserve(EffectSpecs.Num());
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr || EffectSpecs.IsEmpty()) return Results;

    // 게임플레이 이펙트 적용
    for (const auto& EffectSpec : EffectSpecs)
    {
        Results.Emplace(ApplyGameplayEffectSpecToSelf(TargetActor, EffectSpec));
    }

    return Results;
}

FActiveGameplayEffectHandle UGGFBlueprintFunctionLibrary::ApplyGameplayEffectSpecToTarget(const AActor* InstigatorActor,
    const AActor* TargetActor, const FGameplayEffectSpec& EffectSpec)
{
    // 지역 변수 정의
    auto SourceSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(InstigatorActor);
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr) return FActiveGameplayEffectHandle();

    // 게임플레이 이펙트 적용
    return SourceSystem ? SourceSystem->ApplyGameplayEffectSpecToTarget(EffectSpec, TargetSystem) : ApplyGameplayEffectSpecToSelf(TargetActor, EffectSpec);
}

TArray<FActiveGameplayEffectHandle> UGGFBlueprintFunctionLibrary::ApplyGameplayEffectSpecsToTarget(
    const AActor* InstigatorActor, const AActor* TargetActor, const TArray<FGameplayEffectSpec>& EffectSpecs)
{
    // 지역 변수 정의
    TArray<FActiveGameplayEffectHandle> Results;
    Results.Emplace(EffectSpecs.Num());
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr || EffectSpecs.IsEmpty()) return Results;

    // 게임플레이 이펙트 적용
    for (auto EffectSpec : EffectSpecs)
    {
        Results.Emplace(ApplyGameplayEffectSpecToTarget(InstigatorActor, TargetActor, EffectSpec));
    }

    return Results;
}

FActiveGameplayEffectHandle UGGFBlueprintFunctionLibrary::ApplyGameplayEffectToSelf(const AActor* TargetActor,
                                                                                    const TSubclassOf<UGameplayEffect> EffectClass)
{
    // 지역 변수 정의
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr || EffectClass == nullptr) return FActiveGameplayEffectHandle();

    // 게임플레이 이펙트 적용
    return TargetSystem->ApplyGameplayEffectToSelf(EffectClass->GetDefaultObject<UGameplayEffect>(), FGameplayEffectConstants::INVALID_LEVEL, TargetSystem->MakeEffectContext());
}

TArray<FActiveGameplayEffectHandle> UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToSelf(const AActor* TargetActor,
    const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses)
{
    // 지역 변수 선언
    TArray<FActiveGameplayEffectHandle> Results;
    Results.Reserve(EffectClasses.Num());
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr || EffectClasses.IsEmpty()) return Results;

    // 게임플레이 이펙트 적용
    for (auto EffectClass : EffectClasses)
    {
        Results.Emplace(ApplyGameplayEffectToSelf(TargetActor, EffectClass));
    }

    return Results;
}

FActiveGameplayEffectHandle UGGFBlueprintFunctionLibrary::ApplyGameplayEffectToTarget(const AActor* InstigatorActor,
    const AActor* TargetActor, const TSubclassOf<UGameplayEffect> EffectClass)
{
    // 지역 변수 정의
    auto SourceSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(InstigatorActor);
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr || EffectClass == nullptr) return FActiveGameplayEffectHandle();

    // 게임플레이 이펙트 적용
    return SourceSystem ? SourceSystem->ApplyGameplayEffectToTarget(EffectClass->GetDefaultObject<UGameplayEffect>(), TargetSystem) : ApplyGameplayEffectToSelf(TargetActor, EffectClass);
}

TArray<FActiveGameplayEffectHandle> UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToTarget(
    const AActor* InstigatorActor, const AActor* TargetActor, const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses)
{
    // 지역 변수 정의
    TArray<FActiveGameplayEffectHandle> Results;
    Results.Emplace(EffectClasses.Num());
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr || EffectClasses.IsEmpty()) return Results;

    // 게임플레이 이펙트 적용
    for (auto EffectClass : EffectClasses)
    {
        Results.Emplace(ApplyGameplayEffectToTarget(InstigatorActor, TargetActor, EffectClass));
    }

    return Results;
}
