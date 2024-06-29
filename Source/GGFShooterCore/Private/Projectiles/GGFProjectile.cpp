// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectiles/GGFProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Logging.h"
#include "Components/GGFEffectManager.h"

FName AGGFProjectile::ProjectileMovementName(TEXT("ProjectileMovement"));
FName AGGFProjectile::EffectManagerName(TEXT("EffectManager"));

AGGFProjectile::AGGFProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    /* 기본 설정 */
    // 서버 스폰을 위한 리플리케이트
    bReplicates = true;
    SetReplicatingMovement(true);

    // 자동 파괴 시간 설정
    InitialLifeSpan = 20;

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

    /* EffectManager */
    EffectManager = CreateDefaultSubobject<UGGFEffectManager>(EffectManagerName);

    /* 기본 에셋 설정 */
    ConstructorHelpers::FObjectFinder<UStaticMesh> DisplayMeshFinder(TEXT("/Engine/BasicShapes/Sphere"));
    if(DisplayMeshFinder.Succeeded())
    {
        DisplayMesh->SetStaticMesh(DisplayMeshFinder.Object);
        ConstructorHelpers::FObjectFinder<UMaterialInterface> DisplayMeshMaterialFinder(TEXT("/Engine/BasicShapes/BasicShapeMaterial"));
        if(DisplayMeshMaterialFinder.Succeeded()) DisplayMesh->SetMaterial(0, DisplayMeshMaterialFinder.Object);

        DisplayMesh->SetRelativeScale3D(FVector(0.02, 0.02, 0.02));
    }
}

void AGGFProjectile::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 이벤트 바인딩
    if(HasAuthority())
    {
        GetSphereCollider()->OnComponentHit.AddDynamic(this, &ThisClass::OnSphereColliderHit);
    }
}

void AGGFProjectile::BeginPlay()
{
    Super::BeginPlay();

    /* 충돌 무시 설정 */
    SphereCollider->IgnoreActorWhenMoving(GetOwner(), true); // 무기
    SphereCollider->IgnoreActorWhenMoving(GetInstigator(), true); // 캐릭터
}

void AGGFProjectile::NetMulticastSpawnHitEffects_Implementation(const FHitResult& HitResult)
{
    GetEffectManager()->PlayEffectsByHitResult(HitResult);
}

void AGGFProjectile::OnSphereColliderHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
#if WITH_EDITOR
    LOG_ACTOR_DETAIL(Log, TEXT("OtherActor: %s"), *OtherActor->GetName())
#endif

    NetMulticastSpawnHitEffects(Hit);

    Destroy();
}
