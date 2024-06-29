// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GameplayAbilityTransporter.h"

#include "GGFBlueprintFunctionLibrary.h"

void UGameplayAbilityTransporter::GiveAbilitiesToTarget(AActor* Target)
{
    UGGFBlueprintFunctionLibrary::GiveAbilitiesToTarget(AbilitiesToGive, Target);
}
