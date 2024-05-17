// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/GGFExplosiveProjectile.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GEBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AGGFExplosiveProjectile::AGGFExplosiveProjectile()
{
    ExplosionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionSphere"));
    ExplosionSphere->SetupAttachment(RootComponent);
}

void AGGFExplosiveProjectile::BeginPlay()
{
    Super::BeginPlay();

    if(!FMath::IsNearlyZero(ExplosionTime))
    {
        if(const UWorld* World = GetWorld())
        {
            World->GetTimerManager().SetTimer(
            ExplosionTimer,
            FTimerDelegate::CreateUObject(this, &ThisClass::OnExplode),
            ExplosionTime,
            false
            );
        }
    }
}

void AGGFExplosiveProjectile::OnComponentHit_Event_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                                                 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if(bEnableHit)
    {
        if(FMath::IsNearlyZero(DelayTime))
        {
            OnExplode();
        }
        else if(const UWorld* World = GetWorld())
        {
            World->GetTimerManager().SetTimer(
                DelayTimer,
                FTimerDelegate::CreateUObject(this, &ThisClass::OnExplode),
                DelayTime,
                false
            );
        }
    }
}

void AGGFExplosiveProjectile::OnExplode_Implementation()
{
    const UWorld* World = GetWorld();
    if(World == nullptr) return;

    // 타이머 초기화
    if(ExplosionTimer.IsValid())
    {
        World->GetTimerManager().ClearTimer(ExplosionTimer);
        ExplosionTimer.Invalidate();
    }

    if(DelayTimer.IsValid())
    {
        World->GetTimerManager().ClearTimer(DelayTimer);
        DelayTimer.Invalidate();
    }

    // 피격 판정
    DetectExplosionHit();

    OnMulticastExplode();
}

void AGGFExplosiveProjectile::DetectExplosionHit_Implementation()
{
    TArray<AActor*> OverlappingActors;
    ExplosionSphere->GetOverlappingActors(OverlappingActors, AActor::StaticClass());
    for (const AActor* OverlappingActor : OverlappingActors)
    {
        if(UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OverlappingActor))
        {
            // 폭발 중심
            const FVector& ExplosionOrigin = GetActorLocation();

            // 피격 판정을 위한 위치 지정 (자기 자신도 포함됩니다)
            TArray<FVector> TargetLocations;
            GetTargetLocations(OverlappingActor, TargetLocations);

            // TODO 나중에 ApplyRadiusDamage와 비슷한 역할의 GameplayEffect를 만들어지면 1회만 적용하도록 변경
            // 라인 트레이스로 피격 판정
            for (const FVector& TargetLocation : TargetLocations)
            {
                if(UWorld* World = GetWorld())
                {
                    FCollisionQueryParams CollisionQueryParams;
                    CollisionQueryParams.AddIgnoredActor(this);

                    const FVector& Direction = (TargetLocation - ExplosionOrigin).GetSafeNormal();
                    const float Offset = 100.f;
                    const FVector TraceEnd = TargetLocation + Direction * Offset;

                    FHitResult HitResult;
                    World->LineTraceSingleByChannel(
                        HitResult,
                        ExplosionOrigin,
                        TraceEnd,
                        CollisionChannel,
                        CollisionQueryParams
                        );

                    // 피격 대상이 동일, 즉 장애물이 없는 경우
                    if(HitResult.GetActor() == OverlappingActor)
                    {
#if WITH_EDITOR
                        if(bShowDebug)
                            DrawDebugLine(
                                World,
                                ExplosionOrigin,
                                TraceEnd,
                                FColor::Green,
                                false,
                                3,
                                0,
                                2
                                );
#endif

                        // 데미지 적용
                        UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToSystem(EffectsToApply, AbilitySystem);
                    }
                    else
                    {
#if WITH_EDITOR
                        if(bShowDebug)
                            DrawDebugLine(
                                World,
                                ExplosionOrigin,
                                TraceEnd,
                                FColor::Red,
                                false,
                                3,
                                0,
                                2
                                );
#endif
                    }
                }
            }
        }
    }
}

void AGGFExplosiveProjectile::GetTargetLocations(const AActor* Target, TArray<FVector>& TargetLocations)
{
    // null 검사
    if(Target == nullptr) return;

    // 배열 비우기
    TargetLocations.Reset(5);

    // 타깃 액터 바운드 가져오기
    float CollisionRadius;
    float CollisionHalfHeight;
    Target->GetComponentsBoundingCylinder(CollisionRadius, CollisionHalfHeight);

    // 기준 벡터 캐싱
    const FVector& UpVector = Target->GetActorUpVector();
    const FVector& RightVector = Target->GetActorRightVector();

    // TODO Offset 비율 조정은 임의로 했기 때문에 피격 판정이 이상한 경우 이 부분을 의심해보아야 합니다.
    const FVector UpOffset = CollisionHalfHeight * UpVector * 0.8f;
    const FVector RightOffset = CollisionRadius * RightVector * 0.3f;

    // 상하좌우 지점 구하기
    const FVector& TargetCenter = Target->GetActorLocation();
    const FVector TopLocation = TargetCenter + UpOffset;
    const FVector BottomLocation = TargetCenter - UpOffset;
    const FVector RightLocation = TargetCenter + RightOffset;
    const FVector LeftLocation = TargetCenter - RightOffset;

    // 배열 반환
    TargetLocations.Add(TargetCenter);
    TargetLocations.Add(TopLocation);
    TargetLocations.Add(BottomLocation);
    TargetLocations.Add(LeftLocation);
    TargetLocations.Add(RightLocation);
}


void AGGFExplosiveProjectile::OnMulticastExplode_Implementation()
{
    const FVector& ExplosionLocation = GetActorLocation();

    if(ExplosionSound)
        UGameplayStatics::PlaySoundAtLocation(
            this,
            ExplosionSound,
            ExplosionLocation
        );

    if(ExplosionParticle)
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            this,
            ExplosionParticle,
            ExplosionLocation
        );
    }

    if(ExplosionNiagara)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            this,
            ExplosionNiagara,
            ExplosionLocation
        );
    }

    Destroy();
}
