// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectiles/GGFExplosiveProjectile.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"
#include "Components/SphereComponent.h"
#include "GGFShooterGameplayTags.h"

using namespace GGFGameplayTags;

AGGFExplosiveProjectile::AGGFExplosiveProjectile()
{
    // ExplosionArea
    ExplosionArea = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionSphere"));
    ExplosionArea->SetupAttachment(RootComponent);

    // 기본 설정
    ExplosionCueTag = FGameplayCueTag(GameplayCue::Explosion::Default);
}

void AGGFExplosiveProjectile::Destroyed()
{
    // 폭발 이펙트 스폰
    LocalHandleExplosionGameplayCue();

    Super::Destroyed();
}

void AGGFExplosiveProjectile::OnSphereColliderHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                                                 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    Explode();
}

void AGGFExplosiveProjectile::AutoDestroy()
{
    Explode();
}

void AGGFExplosiveProjectile::Explode_Implementation()
{
    // 폭발 범위 내의 모든 액터에 대한 피격 판정
    CheckExplosionArea();

    // 파괴
    Destroy();
}

void AGGFExplosiveProjectile::LocalHandleExplosionGameplayCue()
{
    FGameplayCueParameters GameplayCueParameters;
    GameplayCueParameters.Location = GetActorLocation();
    GameplayCueParameters.Normal = GetActorRotation().Vector();

    UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(this, ExplosionCueTag.GameplayCueTag, EGameplayCueEvent::Executed, GameplayCueParameters);
}

void AGGFExplosiveProjectile::CheckExplosionArea_Implementation()
{
    TArray<AActor*> OverlappingActors;
    ExplosionArea->GetOverlappingActors(OverlappingActors, AActor::StaticClass());
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

                        // 대상에게 데미지 및 추가 GE 적용
                        ApplyEffects(HitResult.GetActor());
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
