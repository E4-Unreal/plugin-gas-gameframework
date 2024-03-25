// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/GGFBlueprintFunctionLibrary.h"

#include "GameplayAbilitySpecHandle.h"
#include "FunctionLibraries/GGFFunctionLibrary.h"

void UGGFBlueprintFunctionLibrary::AddAttributeSetToTarget(const TSubclassOf<UAttributeSet> AttributeSetClass,
    const AActor* TargetActor)
{
    UGGFFunctionLibrary::AddAttributeSetToTarget(AttributeSetClass, TargetActor);
}

void UGGFBlueprintFunctionLibrary::AddAttributeSetsToTarget(
    const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses, const AActor* TargetActor)
{
    UGGFFunctionLibrary::AddAttributeSetsToTarget(AttributeSetClasses, TargetActor);
}

void UGGFBlueprintFunctionLibrary::AddAttributeSetToSystem(const TSubclassOf<UAttributeSet> AttributeSetClass,
                                                          UAbilitySystemComponent* AbilitySystem)
{
    UGGFFunctionLibrary::AddAttributeSetToSystem(AttributeSetClass, AbilitySystem);
}

void UGGFBlueprintFunctionLibrary::AddAttributeSetsToSystem(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses,
    UAbilitySystemComponent* AbilitySystem)
{
    UGGFFunctionLibrary::AddAttributeSetsToSystem(AttributeSetClasses, AbilitySystem);
}

void UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToSelf(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses,
    const AActor* TargetActor)
{
    UGGFFunctionLibrary::ApplyGameplayEffectsToSelf(EffectClasses, TargetActor);
}

void UGGFBlueprintFunctionLibrary::ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass,
                                                            const AActor* TargetActor)
{
    UGGFFunctionLibrary::ApplyGameplayEffectToSelf(EffectClass, TargetActor);
}

void UGGFBlueprintFunctionLibrary::ApplyGameplayEffectToTarget(const TSubclassOf<UGameplayEffect> EffectClass,
                                                              const AActor* Instigator, const AActor* TargetActor)
{
    UGGFFunctionLibrary::ApplyGameplayEffectToTarget(EffectClass, Instigator, TargetActor);
}

void UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToTarget(
    const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, const AActor* Instigator, const AActor* TargetActor)
{
    UGGFFunctionLibrary::ApplyGameplayEffectsToTarget(EffectClasses, Instigator, TargetActor);
}

void UGGFBlueprintFunctionLibrary::ApplyGameplayEffectToSystem(const TSubclassOf<UGameplayEffect> EffectClass,
    UAbilitySystemComponent* AbilitySystem)
{
    UGGFFunctionLibrary::ApplyGameplayEffectToSystem(EffectClass, AbilitySystem);
}

void UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToSystem(
    const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, UAbilitySystemComponent* AbilitySystem)
{
    UGGFFunctionLibrary::ApplyGameplayEffectsToSystem(EffectClasses, AbilitySystem);
}

void UGGFBlueprintFunctionLibrary::ApplyGameplayEffectToTargetSystem(const TSubclassOf<UGameplayEffect> EffectClass,
    UAbilitySystemComponent* Instigator, UAbilitySystemComponent* TargetAbilitySystem)
{
    UGGFFunctionLibrary::ApplyGameplayEffectToTargetSystem(EffectClass, Instigator, TargetAbilitySystem);
}

void UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToTargetSystem(
    const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, UAbilitySystemComponent* Instigator,
    UAbilitySystemComponent* TargetAbilitySystem)
{
    UGGFFunctionLibrary::ApplyGameplayEffectsToTargetSystem(EffectClasses, Instigator, TargetAbilitySystem);
}

FGameplayAbilitySpecHandle UGGFBlueprintFunctionLibrary::GiveAbilityToTarget(const TSubclassOf<UGameplayAbility> AbilityClass,
    const AActor* Target)
{
    return UGGFFunctionLibrary::GiveAbilityToTarget(AbilityClass, Target);
}

TArray<FGameplayAbilitySpecHandle> UGGFBlueprintFunctionLibrary::GiveAbilitiesToTarget(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses,
    const AActor* Target)
{
    return UGGFFunctionLibrary::GiveAbilitiesToTarget(AbilityClasses, Target);
}

FGameplayAbilitySpecHandle UGGFBlueprintFunctionLibrary::GiveAbilityToSystem(const TSubclassOf<UGameplayAbility> AbilityClass,
    UAbilitySystemComponent* AbilitySystem)
{
    return UGGFFunctionLibrary::GiveAbilityToSystem(AbilityClass, AbilitySystem);
}

TArray<FGameplayAbilitySpecHandle> UGGFBlueprintFunctionLibrary::GiveAbilitiesToSystem(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses,
    UAbilitySystemComponent* AbilitySystem)
{
    return UGGFFunctionLibrary::GiveAbilitiesToSystem(AbilityClasses, AbilitySystem);
}
