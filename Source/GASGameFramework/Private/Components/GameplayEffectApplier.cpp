// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GameplayEffectApplier.h"

#include "FunctionLibraries/GGFFunctionLibrary.h"

void UGameplayEffectApplier::ApplyEffectsToTarget(AActor* Target)
{
    UGGFFunctionLibrary::ApplyGameplayEffectsToTarget(EffectsToApply, GetOwner()->GetInstigator(), Target);
}
