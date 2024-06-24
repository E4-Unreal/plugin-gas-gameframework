// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/GGFShotgun.h"

#include "Components/SphereComponent.h"
#include "Interfaces/GGFAimingInterface.h"
#include "Projectiles/GGFDamageableProjectile.h"
#include "Projectiles/GGFProjectile.h"

void AGGFShotgun::OnIDUpdated(int32 NewID)
{
    Super::OnIDUpdated(NewID);

    const auto& FireArmData = GetFireArmData();
    ProjectileNum = FireArmData.PelletNum;
}

void AGGFShotgun::OnFire_Implementation()
{
    // 유효성 검사
    if(!IsValid()) return;

    // 발사체 스폰 정보 계산
    FVector Target = IGGFAimingInterface::Execute_GetTargetLocation(GetOwner());
    FVector FireDirection = (Target - GetMuzzleLocation()).GetSafeNormal();
    TArray<FVector> ProjectileDirections;
    CalculateProjectileDirections(FireDirection, ProjectileDirections);

    // 발사체 스폰
    TArray<AGGFProjectile*> SpawnedProjectiles;
    SpawnedProjectiles.Reserve(ProjectileNum);
    for (const auto& ProjectileDirection : ProjectileDirections)
    {
        auto SpawnedProjectile = SpawnProjectile(ProjectileDirection);
        if(auto SpawnedDamageableProjectile = Cast<AGGFDamageableProjectile>(SpawnedProjectile))
        {
            // 데미지 배율 조정
            SpawnedDamageableProjectile->DamageRatio = 1.f / ProjectileNum;
        }
        SpawnedProjectiles.Emplace(SpawnedProjectile);
    }

    // 서로 간의 충돌 무시 설정
    for (auto SpawnedProjectile : SpawnedProjectiles)
    {
        for (auto OtherSpawnedProjectile : SpawnedProjectiles)
        {
            SpawnedProjectile->GetSphereCollider()->IgnoreActorWhenMoving(OtherSpawnedProjectile, true);
        }
    }
}

void AGGFShotgun::CalculateProjectileDirections(const FVector& FireDirection,
                                                TArray<FVector>& ProjectileDirections) const
{
    // 초기화
    ProjectileDirections.Reset(ProjectileNum);

    //랜덤 시드 설정
    FRandomStream RandomStream;
    RandomStream.GenerateNewSeed();

    for (int32 Count = 0; Count < ProjectileNum; ++Count)
    {
        //랜덤 방향 생성
        FVector RandDirection = RandomStream.VRandCone(FireDirection, FMath::DegreesToRadians(ConeHalfAngle));
        ProjectileDirections.Emplace(RandDirection);
    }
}
