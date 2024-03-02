// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/GEBlueprintFunctionLibrary.h"

#include "FunctionLibraries/GEFunctionLibrary.h"

void UGEBlueprintFunctionLibrary::AddAttributeSet(const TSubclassOf<UAttributeSet> AttributeSetClass,
    UAbilitySystemComponent* AbilitySystem)
{
    UGEFunctionLibrary::AddAttributeSet(AttributeSetClass, AbilitySystem);
}

void UGEBlueprintFunctionLibrary::AddAttributeSets(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses,
    UAbilitySystemComponent* AbilitySystem)
{
    UGEFunctionLibrary::AddAttributeSets(AttributeSetClasses, AbilitySystem);
}

void UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToSelf(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses,
    const AActor* TargetActor)
{
    UGEFunctionLibrary::ApplyGameplayEffectsToSelf(EffectClasses, TargetActor);
}

void UGEBlueprintFunctionLibrary::ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass,
                                                            const AActor* TargetActor)
{
    UGEFunctionLibrary::ApplyGameplayEffectToSelf(EffectClass, TargetActor);
}

void UGEBlueprintFunctionLibrary::ApplyGameplayEffectToTarget(const TSubclassOf<UGameplayEffect> EffectClass,
                                                              const AActor* Instigator, const AActor* TargetActor)
{
    UGEFunctionLibrary::ApplyGameplayEffectToTarget(EffectClass, Instigator, TargetActor);
}

void UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToTarget(
    const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, const AActor* Instigator, const AActor* TargetActor)
{
    UGEFunctionLibrary::ApplyGameplayEffectsToTarget(EffectClasses, Instigator, TargetActor);
}

void UGEBlueprintFunctionLibrary::ApplyGameplayEffectToSystem(const TSubclassOf<UGameplayEffect> EffectClass,
    UAbilitySystemComponent* AbilitySystem)
{
    UGEFunctionLibrary::ApplyGameplayEffectToSystem(EffectClass, AbilitySystem);
}

void UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToSystem(
    const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, UAbilitySystemComponent* AbilitySystem)
{
    UGEFunctionLibrary::ApplyGameplayEffectsToSystem(EffectClasses, AbilitySystem);
}

void UGEBlueprintFunctionLibrary::ApplyGameplayEffectToTargetSystem(const TSubclassOf<UGameplayEffect> EffectClass,
    UAbilitySystemComponent* Instigator, UAbilitySystemComponent* TargetAbilitySystem)
{
    UGEFunctionLibrary::ApplyGameplayEffectToTargetSystem(EffectClass, Instigator, TargetAbilitySystem);
}

void UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToTargetSystem(
    const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, UAbilitySystemComponent* Instigator,
    UAbilitySystemComponent* TargetAbilitySystem)
{
    UGEFunctionLibrary::ApplyGameplayEffectsToTargetSystem(EffectClasses, Instigator, TargetAbilitySystem);
}
