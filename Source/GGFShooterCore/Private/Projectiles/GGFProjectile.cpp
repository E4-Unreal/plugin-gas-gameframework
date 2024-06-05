// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectiles/GGFProjectile.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GGFCombatGameplayTags.h"
#include "Logging.h"

FName AGGFProjectile::ProjectileMovementName(TEXT("ProjectileMovement"));

AGGFProjectile::AGGFProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // 서버 스폰을 위한 리플리케이트
    bReplicates = true;
    SetReplicatingMovement(true);

    /* SphereCollider */
    SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
    SetRootComponent(SphereCollider);
    SphereCollider->InitSphereRadius(1);
    SphereCollider->SetCollisionProfileName("IgnoreOnlyPawn"); // 프로젝트에서 스켈레탈 메시의 오브젝트 타입은 Pawn이 아니라고 가정

    /* DisplayMesh */
    DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DisplayMesh"));
    DisplayMesh->SetupAttachment(RootComponent);
    DisplayMesh->SetCollisionProfileName("NoCollision");

    /* ProjectileMovement */
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(ProjectileMovementName);
    ProjectileMovement->InitialSpeed = 10000;
    ProjectileMovement->MaxSpeed = 10000;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->ProjectileGravityScale = 0.1f;

    // 기본 설정
    HitCueTag = FGameplayCueTag(GGFGameplayTags::GameplayCue::Hit::Default);
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

void AGGFProjectile::Deactivate_Implementation()
{
    // ProjectileMovement
    GetProjectileMovement()->Deactivate();

    // SphereCollider
    GetSphereCollider()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetSphereCollider()->Deactivate();

    // DisplayMesh
    DisplayMesh->SetHiddenInGame(true);

    // ChildrenComponent
    TArray<USceneComponent*> ChildrenComponents;
    GetDisplayMesh()->GetChildrenComponents(true, ChildrenComponents);
    for (auto ChildrenComponent : ChildrenComponents)
    {
        ChildrenComponent->SetHiddenInGame(true);
    }
}

void AGGFProjectile::SetAutoDestroyTimer()
{
    // 중복 호출 방지
    if(AutoDestroyTimer.IsValid()) return;

    // 타이머 설정
    if(AutoDestroyTime <= 0)
    {
        DestroyDeferred();
    }
    else
    {
        GetWorldTimerManager().SetTimer(
            AutoDestroyTimer,
            FTimerDelegate::CreateUObject(this, &ThisClass::DestroyDeferred),
            AutoDestroyTime,
            false
            );
    }
}

void AGGFProjectile::DestroyDeferred()
{
    // 비활성화
    Deactivate();

    // 2초 후 파괴
    SetLifeSpan(2);
}

void AGGFProjectile::LocalHandleHitGameplayCue(const FHitResult& HitResult, const FGameplayTag& EffectTag) const
{
    FGameplayCueParameters GameplayCueParameters;
    auto& EffectContext = GameplayCueParameters.EffectContext;
    EffectContext = FGameplayEffectContextHandle(UAbilitySystemGlobals::Get().AllocGameplayEffectContext());
    EffectContext.AddInstigator(GetInstigator(), GetOwner());
    EffectContext.AddSourceObject(this);
    EffectContext.AddHitResult(HitResult);

    UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(HitResult.GetActor(), EffectTag, EGameplayCueEvent::Executed, GameplayCueParameters);
}

void AGGFProjectile::OnSphereColliderHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
#if WITH_EDITOR
    UE_LOG(LogGGFShooterCore, Log, TEXT("%s::%s > OtherActor: %s"), *StaticClass()->GetName(), *FString(__func__), *OtherActor->GetName())
#endif

    // 로컬에서 피격 효과 스폰
    LocalHandleHitGameplayCue(Hit, HitCueTag.GameplayCueTag);

    // 파괴
    DestroyDeferred();
}

void AGGFProjectile::OnProjectileMovementBounce_Implementation(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
    // TODO ImpactResult.Distance에 따라 크기 조절
    // 트리거 조건 검사
    if(ImpactResult.Distance < BounceThreshold) return;

    // 로컬에서 피격 효과 스폰
    LocalHandleHitGameplayCue(ImpactResult, HitCueTag.GameplayCueTag);
}
