// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/GGFProjectileFireArm.h"

#include "Components/SphereComponent.h"
#include "Interfaces/GGFAimingInterface.h"
#include "Projectiles/GGFDamageableProjectile.h"
#include "Projectiles/GGFProjectile.h"

AGGFProjectileFireArm::AGGFProjectileFireArm()
{
    // 기본 설정
    ProjectileClass = AGGFDamageableProjectile::StaticClass();
}

void AGGFProjectileFireArm::OnFire_Implementation()
{
    // 유효성 검사
    if(!IsValid()) return;

    // 발사체 스폰
    FVector Target = IGGFAimingInterface::Execute_GetTargetLocation(GetOwner());
    FVector FireDirection = (Target - GetMuzzleLocation()).GetSafeNormal();
    auto SpawnedProjectile = SpawnProjectile(FireDirection);
}

void AGGFProjectileFireArm::OnIDUpdated(int32 NewID)
{
    Super::OnIDUpdated(NewID);

    // 변수 선언
    const auto& FireArmData = GetFireArmData();

    // 총알 클래스 설정
    ProjectileClass = FireArmData.DefaultProjectile;
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
    auto SpawnedProjectile = World->SpawnActor<AGGFProjectile>(
                                ProjectileClass,
                                MuzzleLocation,
                                SpawnRotation,
                                SpawnParams
                                );

    // 무시할 액터 설정
    SpawnedProjectile->GetSphereCollider()->IgnoreActorWhenMoving(GetInstigator(), true);
    SpawnedProjectile->GetSphereCollider()->IgnoreActorWhenMoving(GetOwner(), true);

    return SpawnedProjectile;
}

bool AGGFProjectileFireArm::IsValid() const
{
    return ProjectileClass && GetOwner() && GetOwner()->Implements<UGGFAimingInterface>();
}
