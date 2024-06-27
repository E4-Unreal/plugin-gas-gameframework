// Fill out your copyright notice in the Description page of Project Settings.

#include "Effects/GGFParticleConfig.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void UGGFParticleConfig::PlayEffectAtActor(AActor* Actor, bool bAttach)
{
    // 입력 유효성 검사
    if(Actor == nullptr) return;

    // 유효성 검사
    if(ParticleData.ParticleSystem == nullptr) return;

    // 스폰 정보 설정
    FFXSystemSpawnParameters SpawnParams;
    SpawnParams.SystemTemplate = ParticleData.ParticleSystem;
    SpawnParams.Scale = ParticleData.Scale;
    SpawnParams.WorldContextObject = Actor;
    SpawnParams.Location = Actor->GetActorLocation();

    // 파티클 스폰
    if(bAttach)
    {
        SpawnParams.AttachToComponent = Actor->GetRootComponent();
        SpawnParams.LocationType = EAttachLocation::KeepRelativeOffset;
        SpawnEmitterAttachedWithParams(SpawnParams);
    }
    else
    {
        SpawnEmitterAtLocationWithParams(SpawnParams);
    }
}

void UGGFParticleConfig::PlayEffectAtSocket(UPrimitiveComponent* ComponentToAttach, FName SocketName)
{
    // 입력 유효성 검사
    if(ComponentToAttach == nullptr) return;

    // 유효성 검사
    if(ParticleData.ParticleSystem == nullptr) return;

    // 스폰 정보 설정
    FFXSystemSpawnParameters SpawnParams;
    SpawnParams.SystemTemplate = ParticleData.ParticleSystem;
    SpawnParams.Scale = ParticleData.Scale;
    SpawnParams.WorldContextObject = ComponentToAttach;
    SpawnParams.AttachToComponent = ComponentToAttach;
    SpawnParams.AttachPointName = SocketName;
    SpawnParams.LocationType = EAttachLocation::SnapToTarget;

    // 파티클 스폰
    SpawnEmitterAttachedWithParams(SpawnParams);
}

void UGGFParticleConfig::PlayEffectByHitResult(const FHitResult& HitResult, bool bAttach)
{
    // 입력 유효성 검사
    if(!HitResult.bBlockingHit) return;

    // 유효성 검사
    if(ParticleData.ParticleSystem == nullptr) return;

    // 스폰 정보 설정
    FFXSystemSpawnParameters SpawnParams;
    SpawnParams.SystemTemplate = ParticleData.ParticleSystem;
    SpawnParams.Scale = ParticleData.Scale;
    SpawnParams.WorldContextObject = HitResult.GetActor();
    SpawnParams.Location = HitResult.Location;
    SpawnParams.Rotation = HitResult.ImpactNormal.Rotation();

    // 나이아가라 스폰
    if(bAttach)
    {
        SpawnParams.AttachToComponent = HitResult.GetComponent();
        SpawnParams.LocationType = EAttachLocation::KeepRelativeOffset;
        SpawnEmitterAttachedWithParams(SpawnParams);
    }
    else
    {
        SpawnEmitterAtLocationWithParams(SpawnParams);
    }
}

void UGGFParticleConfig::SpawnEmitterAtLocationWithParams(const FFXSystemSpawnParameters& SpawnParams)
{
    UGameplayStatics::SpawnEmitterAtLocation(
        SpawnParams.WorldContextObject,
        Cast<UParticleSystem>(SpawnParams.SystemTemplate),
        SpawnParams.Location,
        SpawnParams.Rotation,
        SpawnParams.Scale
        );
}

void UGGFParticleConfig::SpawnEmitterAttachedWithParams(const FFXSystemSpawnParameters& SpawnParams)
{
    UGameplayStatics::SpawnEmitterAttached(
        Cast<UParticleSystem>(SpawnParams.SystemTemplate),
        SpawnParams.AttachToComponent,
        SpawnParams.AttachPointName,
        SpawnParams.Location,
        SpawnParams.Rotation,
        SpawnParams.Scale,
        SpawnParams.LocationType
        );
}
