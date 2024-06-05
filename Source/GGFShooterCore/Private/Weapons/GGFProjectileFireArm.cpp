// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/GGFProjectileFireArm.h"

#include "Interfaces/GGFAimingInterface.h"
#include "Projectiles/GGFProjectile.h"

AGGFProjectileFireArm::AGGFProjectileFireArm()
{
    // 기본 설정
    ProjectileClass = AGGFProjectile::StaticClass();
}

void AGGFProjectileFireArm::OnFire_Implementation()
{
    // 유효성 검사
    if(!IsValid()) return;

    // 발사체 스폰
    FVector Target;
    IGGFAimingInterface::Execute_GetTarget(GetOwner(), Target);
    FVector FireDirection = (Target - GetMuzzleLocation()).GetSafeNormal();
    SpawnProjectile(FireDirection);
}

AGGFProjectile* AGGFProjectileFireArm::SpawnProjectile(const FVector& Direction)
{
    // World 검사
    UWorld* World = GetWorld();
    if(World == nullptr) return nullptr;

    /* Projectile 스폰 */
    // 스폰 방향 설정
    const FVector MuzzleLocation = GetMuzzleLocation();
    const FRotator SpawnRotation = Direction.Rotation();

    // 스폰 변수 설정
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    // 스폰
    return World->SpawnActor<AGGFProjectile>(
        ProjectileClass,
        MuzzleLocation,
        SpawnRotation,
        SpawnParams
        );
}

bool AGGFProjectileFireArm::IsValid() const
{
    return ProjectileClass && GetOwner() && GetOwner()->Implements<UGGFAimingInterface>();
}
