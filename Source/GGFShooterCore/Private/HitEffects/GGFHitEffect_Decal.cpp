// Fill out your copyright notice in the Description page of Project Settings.

#include "HitEffects/GGFHitEffect_Decal.h"

#include "Kismet/GameplayStatics.h"

void UGGFHitEffect_Decal::SpawnHitEffect(const FHitResult& HitResult) const
{
    // null 검사
    if(DecalMaterial == nullptr) return;

    // HitResult 분석
    const FVector_NetQuantize& ImpactPoint = HitResult.ImpactPoint;
    FRotator HitRotator = (-HitResult.ImpactNormal).Rotation();
    UPrimitiveComponent* TargetComponent = HitResult.GetComponent();
    const FName& HitBoneName = HitResult.BoneName;

    // 데칼 스폰 정보 생성
    const float RandomSize = FMath::RandRange(MinSize, MaxSize);
    const FVector DecalSize = FVector(Depth, RandomSize, RandomSize);
    HitRotator.Add(0, 0, FMath::RandRange(0, 360));

    // 데칼 스폰
    UGameplayStatics::SpawnDecalAttached(
        DecalMaterial,
        DecalSize,
        TargetComponent,
        HitBoneName,
        ImpactPoint,
        HitRotator,
        EAttachLocation::Type::KeepWorldPosition
        );
}
