// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectiles/GGFSpawnableProjectile.h"

void AGGFSpawnableProjectile::OnSphereColliderHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // 스폰
    if(HasAuthority())
    {
        FVector SpawnLocation;
        FRotator SpawnRotation;
        FActorSpawnParameters ActorSpawnParameters;
        ActorSpawnParameters.Instigator = GetInstigator();
        ActorSpawnParameters.Owner = GetOwner();

        if(bUseHitResult)
        {
            SpawnLocation = Hit.ImpactPoint;
            SpawnRotation = Hit.ImpactNormal.ToOrientationRotator();
        }
        else
        {
            SpawnLocation = GetActorLocation();
            SpawnRotation = GetActorRotation();
        }

        GetWorld()->SpawnActor(ActorToSpawn, &SpawnLocation, &SpawnRotation, ActorSpawnParameters);
    }

    Super::OnSphereColliderHit_Implementation(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}
