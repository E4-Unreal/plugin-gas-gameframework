// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectiles/GGFExplosiveProjectile.h"

#include "Components/SphereComponent.h"
#include "Components/GGFExplosiveComponent.h"

AGGFExplosiveProjectile::AGGFExplosiveProjectile()
{
    // ExplosionArea
    ExplosionArea = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionSphere"));
    ExplosionArea->SetupAttachment(RootComponent);

    // ExplosiveComponent
    ExplosiveComponent = CreateDefaultSubobject<UGGFExplosiveComponent>(TEXT("ExplosiveComponent"));
    ExplosiveComponent->Init(ExplosionArea);
}

void AGGFExplosiveProjectile::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    ExplosiveComponent->DamageEffect = DamageClass;
    ExplosiveComponent->AdditionalEffects = AdditionalEffects;
    ExplosiveComponent->FixedDamage = FixedDamage;
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
