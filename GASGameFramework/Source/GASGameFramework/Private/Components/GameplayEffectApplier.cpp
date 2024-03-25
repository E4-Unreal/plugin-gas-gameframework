// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GameplayEffectApplier.h"

#include "FunctionLibraries/GEFunctionLibrary.h"

void UGameplayEffectApplier::ApplyEffectsToTarget(AActor* Target)
{
    UGEFunctionLibrary::ApplyGameplayEffectsToTarget(EffectsToApply, GetOwner()->GetInstigator(), Target);
}
