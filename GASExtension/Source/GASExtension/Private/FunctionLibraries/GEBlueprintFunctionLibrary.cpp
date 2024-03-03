// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/GEBlueprintFunctionLibrary.h"

#include "FunctionLibraries/GEFunctionLibrary.h"

void UGEBlueprintFunctionLibrary::AddAttributeSetToTarget(const TSubclassOf<UAttributeSet> AttributeSetClass,
    const AActor* TargetActor)
{
    UGEFunctionLibrary::AddAttributeSetToTarget(AttributeSetClass, TargetActor);
}

void UGEBlueprintFunctionLibrary::AddAttributeSetsToTarget(
    const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses, const AActor* TargetActor)
{
    UGEFunctionLibrary::AddAttributeSetsToTarget(AttributeSetClasses, TargetActor);
}

void UGEBlueprintFunctionLibrary::AddAttributeSetToSystem(const TSubclassOf<UAttributeSet> AttributeSetClass,
                                                          UAbilitySystemComponent* AbilitySystem)
{
    UGEFunctionLibrary::AddAttributeSetToSystem(AttributeSetClass, AbilitySystem);
}

void UGEBlueprintFunctionLibrary::AddAttributeSetsToSystem(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses,
    UAbilitySystemComponent* AbilitySystem)
{
    UGEFunctionLibrary::AddAttributeSetsToSystem(AttributeSetClasses, AbilitySystem);
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

void UGEBlueprintFunctionLibrary::GiveAbilityToTarget(const TSubclassOf<UGameplayAbility> AbilityClass,
    const AActor* Target)
{
    UGEFunctionLibrary::GiveAbilityToTarget(AbilityClass, Target);
}

void UGEBlueprintFunctionLibrary::GiveAbilitiesToTarget(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses,
    const AActor* Target)
{
    UGEFunctionLibrary::GiveAbilitiesToTarget(AbilityClasses, Target);
}

void UGEBlueprintFunctionLibrary::GiveAbilityToSystem(const TSubclassOf<UGameplayAbility> AbilityClass,
    UAbilitySystemComponent* AbilitySystem)
{
    UGEFunctionLibrary::GiveAbilityToSystem(AbilityClass, AbilitySystem);
}

void UGEBlueprintFunctionLibrary::GiveAbilitiesToSystem(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses,
    UAbilitySystemComponent* AbilitySystem)
{
    UGEFunctionLibrary::GiveAbilitiesToSystem(AbilityClasses, AbilitySystem);
}
