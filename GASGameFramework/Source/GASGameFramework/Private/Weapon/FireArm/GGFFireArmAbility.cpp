// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FireArm/GGFFireArmAbility.h"

#include "Weapon/FireArm/GGFFireArm.h"

void UGGFFireArmAbility::OnRep_Weapon()
{
    Super::OnRep_Weapon();

    // 총기 레퍼런스 캐싱
    AActor* CachedWeapon = GetWeapon();
    FireArm = CachedWeapon == nullptr ? nullptr : Cast<AGGFFireArm>(CachedWeapon);
}
