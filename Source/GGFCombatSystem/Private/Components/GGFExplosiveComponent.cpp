// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFExplosiveComponent.h"

#include "GGFBlueprintFunctionLibrary.h"
#include "GGFBlueprintFunctionLibrary.h"
#include "Logging.h"
#include "Components/SphereComponent.h"
#include "GameplayEffects/GGFDamageBase.h"
#include "GGFGameplayTags.h"
#include "GGFCombatGameplayTags.h"

UGGFExplosiveComponent::UGGFExplosiveComponent()
{
    // 기본 설정
    DamageEffect = UGGFDamageBase::StaticClass();
    DamageType = Data::Damage::Type::Default;
    ExplosionCueTag = FGameplayCueTag(GGFGameplayTags::GameplayCue::Explosion::Default);
}

void UGGFExplosiveComponent::Init(USphereComponent* InExplosionArea)
{
    ExplosionArea = InExplosionArea;

#if WITH_EDITOR
    bValid = ExplosionArea.IsValid();
#endif
}

void UGGFExplosiveComponent::Explode()
{
    if(GetOwner()->HasAuthority())
    {
        // 오버랩된 액터에 폭발 데미지 적용
        if(ExplosionArea.IsValid())
        {
            TArray<AActor*> OverlappingActors;
            ExplosionArea->GetOverlappingActors(OverlappingActors, AActor::StaticClass());
            for (AActor* OverlappingActor : OverlappingActors)
            {
                if(OverlappingActor == GetOwner()) continue;
                ApplyEffects(OverlappingActor);
            }
        }
    }

    // 폭발 효과
    UGGFBlueprintFunctionLibrary::LocalHandleGameplayCue(GetOwner(), ExplosionCueTag);

    // 파괴
    if(bAutoDestroy) GetOwner()->Destroy();
}

float UGGFExplosiveComponent::CalculateDamageRatio(AActor* Target)
{
    const FVector& ExplosionOrigin = GetOwner()->GetActorLocation();

    /* 피격 판정에 따른 데미지 배율 계산 */
    // 피격 카운트
    int32 Count = 0;
    float MinDistance = ExplosionArea->GetScaledSphereRadius();

    // 피격 판정을 위한 위치 지정 (자기 자신도 포함됩니다)
    TArray<FVector> TargetLocations;
    GetLocationsForExplosionDetection(Target, TargetLocations);

    // 라인 트레이스로 피격 판정
    for (const FVector& TargetLocation : TargetLocations)
    {
        if(UWorld* World = Target->GetWorld())
        {
            FCollisionQueryParams CollisionQueryParams;
            CollisionQueryParams.AddIgnoredActor(GetOwner());
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
            if(HitResult.GetActor() == Target)
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
                // 피격 카운트 추가
                Count++;
                MinDistance = FMath::Min(MinDistance, HitResult.Distance);
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

    // 피격 판정 비율
    float HitRatio = Count == 0 ? 0 : Count / static_cast<float>(TargetLocations.Num());

    /* 거리 별 데미지 비율 계산 */
    float InnerRadius = ExplosionArea->GetScaledSphereRadius() * InnerRadiusRatio;
    float OuterRadius = ExplosionArea->GetScaledSphereRadius() - InnerRadius;
    float DistanceRatio = MinDistance <= InnerRadius ? 1 : FMath::Lerp(1.f, 0.1f, (MinDistance - InnerRadius) / OuterRadius);

    /* 최종 데미지 배율 */
    float DamageRatio = HitRatio * DistanceRatio;

#if WITH_EDITOR
    UE_LOG(LogGGFCombatSystem, Log, TEXT("%s > DamageRatio(%f) = HitRatio(%f) * DistanceRatio(%f)"), *Target->GetName(), DamageRatio, HitRatio, DistanceRatio)
#endif

    return DamageRatio;
}

void UGGFExplosiveComponent::GetLocationsForExplosionDetection(AActor* Target, TArray<FVector>& TargetLocations)
{
    // null 검사
    if(Target == nullptr) return;

    TargetLocations.Reset(1);
    TargetLocations.Emplace(Target->GetActorLocation());

    return;

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

void UGGFExplosiveComponent::ApplyEffects(AActor* Target)
{
    // 유효성 검사
    if(Target == nullptr) return;

    // Instigator 가져오기
    AActor* Instigator = GetOwner()->GetInstigator() ? GetOwner()->GetInstigator() : GetOwner();

    // 데미지 적용
    const float DamageRatio = CalculateDamageRatio(Target);
    if(DamageRatio == 0) return; // 피격 판정 실패
    UGGFBlueprintFunctionLibrary::ApplyDamageToTarget(Instigator, Target, DamageEffect, FixedDamage, DamageRatio, DamageType.Tag);

    // 추가 이펙트 적용
    if(DamageRatio > 0)
    {
        UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToTarget(Instigator, Target, AdditionalEffects);
    }
}
