// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GameplayAbilityTransporter.h"

#include "FunctionLibraries/GGFFunctionLibrary.h"


void UGameplayAbilityTransporter::GiveAbilitiesToTarget(AActor* Target)
{
    UGGFFunctionLibrary::GiveAbilitiesToTarget(AbilitiesToGive, Target);
}
