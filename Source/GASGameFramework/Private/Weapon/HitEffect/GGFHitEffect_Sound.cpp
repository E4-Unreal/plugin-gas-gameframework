// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/HitEffect/GGFHitEffect_Sound.h"

#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void UGGFHitEffect_Sound::SpawnHitEffect(const FHitResult& HitResult) const
{
    // null 검사
    if(Sound == nullptr) return;

    // 소리 재생
    UGameplayStatics::PlaySoundAtLocation(
        HitResult.GetComponent(),
        Sound,
        HitResult.ImpactPoint,
        FRotator::ZeroRotator
        );
}
