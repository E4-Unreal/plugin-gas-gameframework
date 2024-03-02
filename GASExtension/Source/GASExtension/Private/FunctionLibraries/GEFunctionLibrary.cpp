// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/GEFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Logging.h"

class UAbilitySystemComponent;

void UGEFunctionLibrary::ApplyGameplayEffectToTarget(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* Instigator, const AActor* Target)
{
    // Instigator AbilitySystem 획득 및 유효성 검사
    UAbilitySystemComponent* InstigatorAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Instigator);
    if(InstigatorAbilitySystem == nullptr)
    {
        LOG_CHECK(LogGASExtension, InstigatorAbilitySystem == nullptr);
        ApplyGameplayEffectToSelf(EffectClass, Target);
        return;
    }

    // Target AbilitySystem 획득 및 유효성 검사
    UAbilitySystemComponent* TargetAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target);
    if(TargetAbilitySystem == nullptr) return;

    // Instigator가 Target에게 Effect 적용
    UGameplayEffect* Effect = EffectClass->GetDefaultObject<UGameplayEffect>();
    InstigatorAbilitySystem->ApplyGameplayEffectToTarget(Effect, TargetAbilitySystem);
}

void UGEFunctionLibrary::ApplyGameplayEffectsToTarget(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses,
    const AActor* Instigator, const AActor* Target)
{
    // 서버에서만 호출
    if(Instigator == nullptr || !Instigator->HasAuthority()) return;

    for (const TSubclassOf<UGameplayEffect> EffectClass : EffectClasses)
    {
        // null 검사
        if(EffectClass == nullptr) continue;

        // Effect 적용
        ApplyGameplayEffectToTarget(EffectClass, Instigator, Target);
    }
}

void UGEFunctionLibrary::ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* Target)
{
    // EffectClass null 검사
    if(EffectClass == nullptr) return;

    // AbilitySystem 획득 및 유효성 검사
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target);
    if(AbilitySystem == nullptr) return;

    // Effect 적용
    const UGameplayEffect* Effect = EffectClass->GetDefaultObject<UGameplayEffect>();
    AbilitySystem->ApplyGameplayEffectToSelf(Effect, UGameplayEffect::INVALID_LEVEL, AbilitySystem->MakeEffectContext());
}

void UGEFunctionLibrary::ApplyGameplayEffectsToSelf(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses,
    const AActor* Target)
{
    // 서버에서만 호출
    if(Target == nullptr || !Target->HasAuthority()) return;

    for (const TSubclassOf<UGameplayEffect> EffectClass : EffectClasses)
    {
        // null 검사
        if(EffectClass == nullptr) continue;

        // Effect 적용
        ApplyGameplayEffectToSelf(EffectClass, Target);
    }
}
