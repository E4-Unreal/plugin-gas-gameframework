// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GameplayEffectApplier.h"

#include "GGFBlueprintFunctionLibrary.h"

void UGameplayEffectApplier::ApplyEffectsToTarget(AActor* Target)
{
    UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToTarget(GetOwner()->GetInstigator(), Target, EffectsToApply);
}
