﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FireArm/GEProjectileFireArm.h"

#include "Weapon/Interface/GEAimingInterface.h"
#include "Weapon/Projectile/GEProjectile.h"

void AGEProjectileFireArm::OnFire_Implementation()
{
    // null 검사
    if(ProjectileClass == nullptr || GetOwner() == nullptr) return;

    // AimingInterface 구현 검사
    if(!GetOwner()->GetClass()->ImplementsInterface(UGEAimingInterface::StaticClass())) return;

    // World 검사
    UWorld* World = GetWorld();
    if(World == nullptr) return;

    /* Projectile 스폰 */
    // 스폰 방향 설정
    FVector Target;
    IGEAimingInterface::Execute_GetTarget(GetOwner(), Target);
    const FVector& MuzzleLocation = GetMuzzleLocation();
    const FRotator& SpawnRotation = (Target - MuzzleLocation).GetSafeNormal().Rotation();

    // 스폰 변수 설정
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    // 스폰
    World->SpawnActor(
        ProjectileClass,
        &MuzzleLocation,
        &SpawnRotation,
        SpawnParams
        );
}
