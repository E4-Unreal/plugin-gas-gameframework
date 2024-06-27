// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectiles/GGFExplosiveProjectile.h"

#include "Components/SphereComponent.h"
#include "Components/GGFExplosiveComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AGGFExplosiveProjectile::AGGFExplosiveProjectile()
{
    /* 기본 설정 */
    Damage = 50;

    /* SphereCollider */
    GetSphereCollider()->SetSphereRadius(6);

    /* DisplayMesh */
    GetDisplayMesh()->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));

    /* ProjectileMovement */
    GetProjectileMovement()->MaxSpeed = 5000;
    GetProjectileMovement()->InitialSpeed = 5000;
    GetProjectileMovement()->ProjectileGravityScale = 1;

    /* ExplosionArea */
    ExplosionArea = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionSphere"));
    ExplosionArea->SetupAttachment(RootComponent);
    ExplosionArea->SetSphereRadius(128);

    /* ExplosiveComponent */
    ExplosiveComponent = CreateDefaultSubobject<UGGFExplosiveComponent>(TEXT("ExplosiveComponent"));
    ExplosiveComponent->Init(ExplosionArea);
}

void AGGFExplosiveProjectile::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // TODO 리팩토링 (구조체 혹은 데이터 에셋으로 대체)
    //ExplosiveComponent
    ExplosiveComponent->DamageEffect = DamageEffect;
    ExplosiveComponent->EffectsToApply = EffectsToApply;
    ExplosiveComponent->Damage = Damage;
    ExplosiveComponent->DamageType = DamageType;
}

void AGGFExplosiveProjectile::Destroyed()
{
    ExplosiveComponent->Explode();

    Super::Destroyed();
}

void AGGFExplosiveProjectile::OnSphereColliderHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                                                 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    Destroy();
}
