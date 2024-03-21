// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/Projectile/GEProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AGEProjectile::AGEProjectile()
{
    // 서버 스폰을 위한 리플리케이트
    bReplicates = true;

    // 콜라이더 설정
    SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
    SphereCollider->IgnoreActorWhenMoving(GetOwner(), true); // 무기 무시
    SphereCollider->IgnoreActorWhenMoving(GetInstigator(), true); // 캐릭터 무시
    SphereCollider->InitSphereRadius(1);
    SphereCollider->SetCollisionProfileName("IgnoreOnlyPawn"); // 프로젝트에서 스켈레탈 메시의 오브젝트 타입은 Pawn이 아니라고 가정

    // 발사체 움직임 설정
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 71500;
    ProjectileMovement->MaxSpeed = 71500;
}

void AGEProjectile::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 서버에서만 히트 이벤트 바인딩
    if(HasAuthority())
    {
        SphereCollider->OnComponentHit.AddDynamic(this, &ThisClass::OnComponentHit_Event);
    }
}

void AGEProjectile::OnComponentHit_Event_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // TODO 피지컬 머티리얼에 따라 관통 처리

    // 히트 이벤트 호출
    OnHit(Hit);

    // 멀티캐스트 이벤트 호출
    OnMulticastHit(Hit);
}

void AGEProjectile::OnHit_Implementation(const FHitResult& HitResult)
{
    // TODO 데미지 적용 등 서버에서 처리할 기능 구현
}

void AGEProjectile::OnMulticastHit_Implementation(const FHitResult& HitResult)
{
    // TODO 피격 효과 스폰처럼 멀티캐스트로 처리할 기능 구현
}
