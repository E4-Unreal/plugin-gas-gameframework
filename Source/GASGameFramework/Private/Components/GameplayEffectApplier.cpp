// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GameplayEffectApplier.h"

#include "GEBlueprintFunctionLibrary.h"

void UGameplayEffectApplier::ApplyEffectsToTarget(AActor* Target)
{
    UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToTarget(EffectsToApply, GetOwner()->GetInstigator(), Target);
}
