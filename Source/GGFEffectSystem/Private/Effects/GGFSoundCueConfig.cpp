// Fill out your copyright notice in the Description page of Project Settings.

#include "Effects/GGFSoundCueConfig.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void UGGFSoundCueConfig::PlayEffectAtActor(AActor* Actor, bool bAttach)
{
    // 유효성 검사
    if(SoundCueData.SoundCue == nullptr) return;

    // 사운드 큐 재생
    if(bAttach)
    {
        UGameplayStatics::SpawnSoundAttached(
            SoundCueData.SoundCue,
            Actor->GetRootComponent(),
            NAME_None,
            FVector(ForceInit),
            FRotator::ZeroRotator,
            EAttachLocation::SnapToTarget,
            false,
            SoundCueData.VolumeMultiplier,
            SoundCueData.PitchMultiplier,
            SoundCueData.StartTime
            );
    }
    else
    {
        UGameplayStatics::PlaySoundAtLocation(
            Actor,
            SoundCueData.SoundCue,
            Actor->GetActorLocation(),
            FRotator::ZeroRotator,
            SoundCueData.VolumeMultiplier,
            SoundCueData.PitchMultiplier,
            SoundCueData.StartTime
            );
    }
}

void UGGFSoundCueConfig::PlayEffectAtSocket(UPrimitiveComponent* ComponentToAttach, FName SocketName)
{
    // 입력 유효성 검사
    if(ComponentToAttach == nullptr) return;

    // 유효성 검사
    if(SoundCueData.SoundCue == nullptr) return;

    // 사운드 큐 재생
    UGameplayStatics::SpawnSoundAttached(
        SoundCueData.SoundCue,
        ComponentToAttach,
        SocketName,
        FVector(ForceInit),
        FRotator::ZeroRotator,
        EAttachLocation::SnapToTarget,
        false,
        SoundCueData.VolumeMultiplier,
        SoundCueData.PitchMultiplier,
        SoundCueData.StartTime
        );
}

void UGGFSoundCueConfig::PlayEffectByHitResult(const FHitResult& HitResult, bool bAttach)
{
    // 입력 유효성 검사
    if(!HitResult.bBlockingHit) return;

    // 유효성 검사
    if(SoundCueData.SoundCue == nullptr) return;

    // 사운드 큐 재생
    if(bAttach)
    {
        UGameplayStatics::SpawnSoundAttached(
            SoundCueData.SoundCue,
            HitResult.GetComponent(),
            NAME_None,
            HitResult.ImpactPoint,
            HitResult.ImpactNormal.Rotation(),
            EAttachLocation::KeepRelativeOffset,
            false,
            SoundCueData.VolumeMultiplier,
            SoundCueData.PitchMultiplier,
            SoundCueData.StartTime
            );
    }
    else
    {
        UGameplayStatics::PlaySoundAtLocation(
            HitResult.GetActor(),
            SoundCueData.SoundCue,
            HitResult.ImpactPoint,
            HitResult.ImpactNormal.Rotation(),
            SoundCueData.VolumeMultiplier,
            SoundCueData.PitchMultiplier,
            SoundCueData.StartTime
            );
    }
}
