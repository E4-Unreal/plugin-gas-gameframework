// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/HitEffect/GGFHitEffect_SplatterDecal.h"

void UGGFHitEffect_SplatterDecal::SpawnHitEffect(const FHitResult& HitResult) const
{
    // null 검사
    if(DecalMaterial == nullptr) return;

    // 피격 대상으로부터 World 가져오기
    UWorld* World = HitResult.GetActor()->GetWorld();
    if(World == nullptr) return;

    /* 라인 트레이스 */

    // 피격 지점에서 추가 라인 트레이스
    const FVector& TraceStart = HitResult.ImpactPoint;
    const FVector Direction = (HitResult.TraceEnd - HitResult.TraceStart).GetSafeNormal();
    const FVector TraceEnd = TraceStart + Direction * Distance;

    // 피격 대상은 제외
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(HitResult.GetActor());

    // 라인 트레이스 실행
    FHitResult SplatterHitResult;
    World->LineTraceSingleByChannel(
        SplatterHitResult,
        TraceStart,
        TraceEnd,
        ECC_Visibility,
        CollisionQueryParams
        );

    // Splatter 데칼 스폰
    Super::SpawnHitEffect(SplatterHitResult);
}
