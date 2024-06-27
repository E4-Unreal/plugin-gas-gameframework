// Fill out your copyright notice in the Description page of Project Settings.

#include "Effects/GGFNiagaraConfig.h"

#include "NiagaraFunctionLibrary.h"
#include "Particles/ParticleSystemComponent.h"

void UGGFNiagaraConfig::PlayEffectAtActor(AActor* Actor, bool bAttach)
{
    // 입력 유효성 검사
    if(Actor == nullptr) return;

    // 유효성 검사
    if(NiagaraData.NiagaraSystem == nullptr) return;

    // 스폰 정보 설정
    FFXSystemSpawnParameters SpawnParams;
    SpawnParams.SystemTemplate = NiagaraData.NiagaraSystem;
    SpawnParams.Scale = NiagaraData.Scale;
    SpawnParams.WorldContextObject = Actor;
    SpawnParams.Location = Actor->GetActorLocation();

    // 나이아가라 스폰
    if(bAttach)
    {
        SpawnParams.AttachToComponent = Actor->GetRootComponent();
        SpawnParams.LocationType = EAttachLocation::KeepRelativeOffset;
        UNiagaraFunctionLibrary::SpawnSystemAttachedWithParams(SpawnParams);
    }
    else
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocationWithParams(SpawnParams);
    }
}

void UGGFNiagaraConfig::PlayEffectAtSocket(UPrimitiveComponent* ComponentToAttach, FName SocketName)
{
    // 입력 유효성 검사
    if(ComponentToAttach == nullptr) return;

    // 유효성 검사
    if(NiagaraData.NiagaraSystem == nullptr) return;

    // 스폰 정보 설정
    FFXSystemSpawnParameters SpawnParams;
    SpawnParams.SystemTemplate = NiagaraData.NiagaraSystem;
    SpawnParams.Scale = NiagaraData.Scale;
    SpawnParams.WorldContextObject = ComponentToAttach;
    SpawnParams.AttachToComponent = ComponentToAttach;
    SpawnParams.AttachPointName = SocketName;
    SpawnParams.LocationType = EAttachLocation::SnapToTarget;

    // 나이아가라 스폰
    UNiagaraFunctionLibrary::SpawnSystemAttachedWithParams(SpawnParams);
}

void UGGFNiagaraConfig::PlayEffectByHitResult(const FHitResult& HitResult, bool bAttach)
{
    // 입력 유효성 검사
    if(!HitResult.bBlockingHit) return;

    // 유효성 검사
    if(NiagaraData.NiagaraSystem == nullptr) return;

    // 스폰 정보 설정
    FFXSystemSpawnParameters SpawnParams;
    SpawnParams.SystemTemplate = NiagaraData.NiagaraSystem;
    SpawnParams.Scale = NiagaraData.Scale;
    SpawnParams.WorldContextObject = HitResult.GetActor();
    SpawnParams.Location = HitResult.Location;
    SpawnParams.Rotation = HitResult.ImpactNormal.Rotation();

    // 나이아가라 스폰
    if(bAttach)
    {
        SpawnParams.AttachToComponent = HitResult.GetComponent();
        SpawnParams.LocationType = EAttachLocation::KeepRelativeOffset;
        UNiagaraFunctionLibrary::SpawnSystemAttachedWithParams(SpawnParams);
    }
    else
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocationWithParams(SpawnParams);
    }
}
