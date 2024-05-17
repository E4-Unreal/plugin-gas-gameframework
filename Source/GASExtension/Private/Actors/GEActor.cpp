// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GEActor.h"

#include "AbilitySystem/GEAbilitySystem.h"
#include "Components/GEGameplayEventManager.h"

FName AGEActor::AbilitySystemName(TEXT("AbilitySystem"));
FName AGEActor::GameplayEventManagerName(TEXT("GameplayEventManager"));

AGEActor::AGEActor(const FObjectInitializer& ObjectInitializer)
{
    /* AbilitySystem */
    AbilitySystem = CreateDefaultSubobject<UGEAbilitySystem>(AbilitySystemName);

    /* GameplayEventManager */
    GameplayEventManager = CreateDefaultSubobject<UGEGameplayEventManager>(GameplayEventManagerName);
}
