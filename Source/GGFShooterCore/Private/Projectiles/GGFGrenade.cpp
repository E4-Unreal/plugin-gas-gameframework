// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectiles/GGFGrenade.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayEffects/GGFDamage.h"

AGGFGrenade::AGGFGrenade()
{
    /* 기본 설정 */
    DamageEffect = UGGFDamage::StaticClass();

    /* ProjectileMovement */
    GetProjectileMovement()->MaxSpeed = 1000;
    GetProjectileMovement()->InitialSpeed = 1000;
    GetProjectileMovement()->Bounciness = 0.3;
    GetProjectileMovement()->bShouldBounce = true;
}

void AGGFGrenade::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 바운스 설정
    GetProjectileMovement()->bShouldBounce = bShouldBounce;

    // 이벤트 바인딩
    if(HasAuthority())
    {
        if(bShouldBounce)
        {
            GetSphereCollider()->OnComponentHit.RemoveDynamic(this, &ThisClass::OnSphereColliderHit);
            GetProjectileMovement()->OnProjectileBounce.AddDynamic(this, &ThisClass::OnProjectileBounce);
            SetLifeSpan(ExplosionTime);
        }
    }
}

void AGGFGrenade::OnProjectileBounce_Implementation(const FHitResult& ImpactResult,
    const FVector& ImpactVelocity)
{
    if(ImpactResult.Distance < BounceThreshold) return;

    NetMulticastSpawnHitEffects(ImpactResult);
}
