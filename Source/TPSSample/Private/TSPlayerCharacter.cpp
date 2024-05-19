// Fill out your copyright notice in the Description page of Project Settings.

#include "TSPlayerCharacter.h"

class UTSPlayerAbilitySystem;

ATSPlayerCharacter::ATSPlayerCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UTSPlayerAbilitySystem>(AbilitySystemName))
{

}
