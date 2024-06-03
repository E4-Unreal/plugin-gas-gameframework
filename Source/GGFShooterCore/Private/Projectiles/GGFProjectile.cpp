// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectiles/GGFProjectile.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GGFShooterGameplayTags.h"

using namespace GGFGameplayTags;

FName AGGFProjectile::ProjectileMovementName(TEXT("ProjectileMovement"));

AGGFProjectile::AGGFProjectile()
{
    // 서버 스폰을 위한 리플리케이트
    SetReplicates(true);
    SetReplicatingMovement(true);

    // 콜라이더 설정
    SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
    SetRootComponent(SphereCollider);
    SphereCollider->InitSphereRadius(1);
    SphereCollider->SetCollisionProfileName("IgnoreOnlyPawn"); // 프로젝트에서 스켈레탈 메시의 오브젝트 타입은 Pawn이 아니라고 가정

    // 발사체 움직임 설정
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(ProjectileMovementName);
    ProjectileMovement->InitialSpeed = 71500;
    ProjectileMovement->MaxSpeed = 71500;

    // 기본 설정
    HitCueTag = FGameplayCueTag(GameplayCue::Hit::Default);
}

void AGGFProjectile::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // SphereCollider::OnComponentHit 이벤트 바인딩 여부 확인
    if(bEnableHitTrigger)
    {
        // 이벤트 바인딩
        GetSphereCollider()->OnComponentHit.AddDynamic(this, &ThisClass::OnSphereColliderHit);
    }
    else
    {
        // 바운스 설정
        GetProjectileMovement()->bShouldBounce = true;
        GetProjectileMovement()->OnProjectileBounce.AddDynamic(this, &ThisClass::OnProjectileMovementBounce);
    }
}

void AGGFProjectile::BeginPlay()
{
    Super::BeginPlay();

    // 자동 파괴 타이머 설정
    SetAutoDestroyTimer();

    /* 충돌 무시 설정 */
    SphereCollider->IgnoreActorWhenMoving(GetOwner(), true); // 무기
    SphereCollider->IgnoreActorWhenMoving(GetInstigator(), true); // 캐릭터
}

void AGGFProjectile::Destroyed()
{
    // 타이머 초기화
    if(AutoDestroyTimer.IsValid()) AutoDestroyTimer.Invalidate();

    Super::Destroyed();
}

void AGGFProjectile::SetAutoDestroyTimer()
{
    // 중복 호출 방지
    if(AutoDestroyTimer.IsValid()) return;

    // 타이머 설정
    if(AutoDestroyTime <= 0)
    {
        AutoDestroy();
    }
    else
    {
        GetWorldTimerManager().SetTimer(
            AutoDestroyTimer,
            FTimerDelegate::CreateUObject(this, &ThisClass::AutoDestroy),
            AutoDestroyTime,
            false
            );
    }
}

void AGGFProjectile::AutoDestroy()
{
    Destroy();
}

void AGGFProjectile::LocalHandleHitGameplayCue(const FHitResult& HitResult, const FGameplayTag& EffectTag) const
{
    FGameplayCueParameters GameplayCueParameters;

    if(GetInstigator())
    {
        GameplayCueParameters.EffectContext = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetInstigator())->MakeEffectContext();
        GameplayCueParameters.EffectContext.AddHitResult(HitResult);
    }
    else
    {
        GameplayCueParameters.Location = HitResult.ImpactPoint;
        GameplayCueParameters.Normal = HitResult.ImpactNormal;
    }

    UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(HitResult.GetActor(), EffectTag, EGameplayCueEvent::Executed, GameplayCueParameters);
}

void AGGFProjectile::OnSphereColliderHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // 로컬에서 피격 효과 스폰
    LocalHandleHitGameplayCue(Hit, HitCueTag.GameplayCueTag);

    // 파괴
    Destroy();
}

void AGGFProjectile::OnProjectileMovementBounce_Implementation(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
    // TODO ImpactResult.Distance에 따라 크기 조절
    // 트리거 조건 검사
    if(ImpactResult.Distance < BounceThreshold) return;

    // 로컬에서 피격 효과 스폰
    LocalHandleHitGameplayCue(ImpactResult, HitCueTag.GameplayCueTag);
}
