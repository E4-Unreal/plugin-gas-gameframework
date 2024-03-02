// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/GEBlueprintFunctionLibrary.h"

#include "FunctionLibraries/GEFunctionLibrary.h"

void UGEBlueprintFunctionLibrary::ApplyGameplayEffectToTarget(const TSubclassOf<UGameplayEffect> EffectClass,
                                                              const AActor* Instigator, const AActor* Target)
{
    UGEFunctionLibrary::ApplyGameplayEffectToTarget(EffectClass, Instigator, Target);
}

void UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToTarget(
    const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses, const AActor* Instigator, const AActor* Target)
{
    UGEFunctionLibrary::ApplyGameplayEffectsToTarget(EffectClasses, Instigator, Target);
}

void UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToSelf(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses,
    const AActor* Target)
{
    UGEFunctionLibrary::ApplyGameplayEffectsToSelf(EffectClasses, Target);
}

void UGEBlueprintFunctionLibrary::ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass,
                                                            const AActor* Target)
{
    UGEFunctionLibrary::ApplyGameplayEffectToSelf(EffectClass, Target);
}
