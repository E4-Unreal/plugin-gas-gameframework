// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFFireArmAbility.h"

#include "Weapons/GGFFireArm.h"

bool UGGFFireArmAbility::InternalCanActivate()
{
    return Super::InternalCanActivate() && GetFireArm();
}
