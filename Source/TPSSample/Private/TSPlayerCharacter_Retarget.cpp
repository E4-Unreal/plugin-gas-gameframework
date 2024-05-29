// Fill out your copyright notice in the Description page of Project Settings.

#include "TSPlayerCharacter_Retarget.h"

class UTSPlayerAbilitySystem;

ATSPlayerCharacter_Retarget::ATSPlayerCharacter_Retarget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UTSPlayerAbilitySystem>(AbilitySystemName))
{

}
