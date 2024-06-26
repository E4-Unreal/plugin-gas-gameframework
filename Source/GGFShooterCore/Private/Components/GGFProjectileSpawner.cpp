// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFProjectileSpawner.h"

#include "GGFBlueprintFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Projectiles/GGFProjectile.h"
#include "GGFShooterGameplayTags.h"

UGGFProjectileSpawner::UGGFProjectileSpawner()
{
    MuzzleCueTag.GameplayCueTag = GameplayCue::FireArm::Muzzle::Default;
}

void UGGFProjectileSpawner::Init(USkeletalMeshComponent* InSkeletalMesh)
{
    SkeletalMesh = InSkeletalMesh;
    bValid = SkeletalMesh.IsValid() && SkeletalMesh->DoesSocketExist(MuzzleSocketName) && ProjectileClass;
}

void UGGFProjectileSpawner::FireForward()
{
    // 유효성 검사
    if(ProjectileClass == nullptr) return;

    // 스폰 정보 계산
    FVector SpawnLocation;
    FRotator SpawnRotation;
    if(SkeletalMesh.IsValid() && SkeletalMesh->DoesSocketExist(MuzzleSocketName))
    {
        SpawnLocation = SkeletalMesh->GetSocketLocation(MuzzleSocketName);
        SpawnRotation = SkeletalMesh->GetSocketRotation(MuzzleSocketName);
    }
    else
    {
        SpawnLocation = GetOwner()->GetActorLocation();
        SpawnRotation = GetOwner()->GetActorRotation();
    }

    // 총구 이펙트 재생
    PlayMuzzleGameplayCue(SpawnLocation, SpawnRotation);

    // 총알 스폰
    SpawnProjectile(SpawnLocation, SpawnRotation);
}

void UGGFProjectileSpawner::FireToTarget(const FVector& TargetLocation)
{
    // 유효성 검사
    if(ProjectileClass == nullptr) return;

    // 스폰 정보 계산
    FVector SpawnLocation;
    if(SkeletalMesh.IsValid() && SkeletalMesh->DoesSocketExist(MuzzleSocketName))
    {
        SpawnLocation = SkeletalMesh->GetSocketLocation(MuzzleSocketName);
    }
    else
    {
        SpawnLocation = GetOwner()->GetActorLocation();
    }

    FRotator SpawnRotation = (TargetLocation - SpawnLocation).ToOrientationRotator();

    // 총알 스폰
    SpawnProjectile(SpawnLocation, SpawnRotation);
}

AGGFProjectile* UGGFProjectileSpawner::SpawnProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation)
{
    // 스폰 변수 설정
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = GetOwner();
    SpawnParams.Instigator = GetOwner()->GetInstigator();

    // 스폰
    auto SpawnedProjectile = GetOwner()->GetWorld()->SpawnActor<AGGFProjectile>(
                                ProjectileClass,
                                SpawnLocation,
                                SpawnRotation,
                                SpawnParams
                                );

    // 무시할 액터 설정
    SpawnedProjectile->GetSphereCollider()->IgnoreActorWhenMoving(SpawnParams.Owner, true);
    SpawnedProjectile->GetSphereCollider()->IgnoreActorWhenMoving(SpawnParams.Instigator, true);

    return SpawnedProjectile;
}

void UGGFProjectileSpawner::PlayMuzzleGameplayCue(const FVector& SpawnLocation, const FRotator& SpawnRotation)
{
    FTransform SpawnTransform(SpawnRotation, SpawnLocation);
    UGGFBlueprintFunctionLibrary::LocalHandleGameplayCueWithTransform(GetOwner(), MuzzleCueTag, SpawnTransform);
}
