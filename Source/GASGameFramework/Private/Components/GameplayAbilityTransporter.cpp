// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GameplayAbilityTransporter.h"

#include "GEBlueprintFunctionLibrary.h"


void UGameplayAbilityTransporter::GiveAbilitiesToTarget(AActor* Target)
{
    UGEBlueprintFunctionLibrary::GiveAbilitiesToTarget(AbilitiesToGive, Target);
}
