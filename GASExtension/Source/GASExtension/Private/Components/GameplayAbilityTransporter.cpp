// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GameplayAbilityTransporter.h"

#include "FunctionLibraries/GEFunctionLibrary.h"


void UGameplayAbilityTransporter::GiveAbilitiesToTarget(AActor* Target)
{
    UGEFunctionLibrary::GiveAbilitiesToTarget(AbilitiesToGive, Target);
}
