// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/HitEffect/GEHitEffect_Particle.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void UGEHitEffect_Particle::SpawnHitEffect(const FHitResult& HitResult) const
{
    // null 검사
    if(ParticleSystem == nullptr) return;

    // HitResult 분석
    const FVector HitDirection = HitResult.TraceEnd - HitResult.TraceStart;
    const FVector_NetQuantize& ImpactPoint = HitResult.ImpactPoint;
    const FRotator& ImpactRotator = FRotationMatrix::MakeFromZ(-HitDirection).Rotator();
    UPrimitiveComponent* ComponentToAttach = HitResult.GetComponent();

    // 파티클 시스템 스폰
    UParticleSystemComponent* SpawnedSystem = UGameplayStatics::SpawnEmitterAttached(
            ParticleSystem,
            ComponentToAttach,
            NAME_None,
            ImpactPoint,
            ImpactRotator,
            EAttachLocation::Type::KeepWorldPosition,
            true
            );

    // 파티클 시스템 크기 조정
    if(SpawnedSystem)
        SpawnedSystem->SetWorldScale3D(Scale);
}
