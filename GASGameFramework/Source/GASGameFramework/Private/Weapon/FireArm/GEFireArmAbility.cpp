// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FireArm/GEFireArmAbility.h"

#include "Weapon/FireArm/GEFireArm.h"

void UGEFireArmAbility::OnRep_Weapon()
{
    Super::OnRep_Weapon();

    // 총기 레퍼런스 캐싱
    AActor* CachedWeapon = GetWeapon();
    FireArm = CachedWeapon == nullptr ? nullptr : Cast<AGEFireArm>(CachedWeapon);
}
