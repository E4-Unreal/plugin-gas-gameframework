// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GEActor.h"

#include "AbilitySystem/GEAbilitySystem.h"

FName AGEActor::AbilitySystemName(TEXT("AbilitySystem"));

AGEActor::AGEActor(const FObjectInitializer& ObjectInitializer)
{
    /* AbilitySystem */
    AbilitySystem = CreateDefaultSubobject<UGEAbilitySystem>(AbilitySystemName);
}
