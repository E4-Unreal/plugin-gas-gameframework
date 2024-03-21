// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FireArm/GEHitScanFireArm.h"

#include "FunctionLibraries/GEFunctionLibrary.h"
#include "Weapon/HitEffect/GEHitEffectDefinition.h"
#include "Weapon/Interface/GEAimingInterface.h"

void AGEHitScanFireArm::OnFire_Implementation()
{
    if(GetOwner() && GetOwner()->GetClass()->ImplementsInterface(UGEAimingInterface::StaticClass()))
    {
        const UWorld* World = GetWorld();
        if(World == nullptr) return;

        /* 라인 트레이스 설정 */

        // 라인 트레이스 시작 위치
        const FVector& TraceStart = GetMuzzleLocation();

        // 발사 방향
        FVector Target;
        IGEAimingInterface::Execute_GetTarget(GetOwner(), Target);
        const FVector& Direction = (Target - TraceStart).GetSafeNormal();

        // 라인 트레이스 종료 위치
        const FVector& TraceEnd = TraceStart + MaxDistance * Direction;

        // 무기 및 소유자는 라인 트레이스 대상에서 제외
        FCollisionQueryParams CollisionQueryParams;
        CollisionQueryParams.AddIgnoredActor(this);
        CollisionQueryParams.AddIgnoredActor(GetOwner());
        CollisionQueryParams.bReturnPhysicalMaterial = true;

        // 라인 트레이스 실행
        FHitResult HitResult;
        World->LineTraceSingleByChannel(
            HitResult,
            TraceStart,
            TraceEnd,
            ECC_Visibility,
            CollisionQueryParams
            );

#if WITH_EDITOR
        // 디버그 시각화
        if(bEnableDebugLine)
        {
            if(HitResult.bBlockingHit)
            {
                DrawDebugLine(World, TraceStart, HitResult.ImpactPoint, FColor::Red, false, 2);
                DrawDebugLine(World, HitResult.ImpactPoint, TraceEnd, FColor::Green, false, 2);
            }
            else
            {
                DrawDebugLine(World, TraceStart, Target, FColor::Red, false, 2);
            }
        }
#endif


        // 히트 이벤트 처리
        OnHit(HitResult);
    }
}

void AGEHitScanFireArm::OnHit_Implementation(const FHitResult& HitResult)
{
    // 서버에서만 실행 가능합니다.
    if(!HasAuthority()) return;

    // GE 적용
    UGEFunctionLibrary::ApplyGameplayEffectsToTarget(EffectsToApply, GetInstigator(), HitResult.GetActor());

    // 멀티캐스트
    OnMulticastHit(HitResult);
}

void AGEHitScanFireArm::OnMulticastHit_Implementation(const FHitResult& HitResult)
{
    HitEffect->SpawnHitEffect(HitResult);
}
