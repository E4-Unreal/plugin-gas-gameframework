// Fill out your copyright notice in the Description page of Project Settings.

#include "Turrets/GGFSimpleTurret.h"

#include "Components/CapsuleComponent.h"
#include "Components/GGFProjectileSpawner.h"

AGGFSimpleTurret::AGGFSimpleTurret(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* 기본 설정 */

    // 리플리케이트 설정
    bReplicates = true;

    /* CapsuleComponent */
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    SetRootComponent(CapsuleComponent);

    /* SkeletalMesh */
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMesh->SetupAttachment(RootComponent);
    SkeletalMesh->SetCollisionProfileName("CharacterMesh");

    /* ProjectileSpawner */
    ProjectileSpawner = CreateDefaultSubobject<UGGFProjectileSpawner>(TEXT("ProjectileSpawner"));
    ProjectileSpawner->Init(SkeletalMesh);

    /* EffectManager */
    EffectManager = CreateDefaultSubobject<UGGFEffectManager>(TEXT("EffectManager"));
}

void AGGFSimpleTurret::BeginPlay()
{
    Super::BeginPlay();

    if(bAutoActivate)
    {
        Execute_Activate(this, this);
    }
}

void AGGFSimpleTurret::Destroyed()
{
    // 비활성화
    if(bActive) Execute_Deactivate(this, this);

    // 폭발 효과 스폰
    GetEffectManager()->PlayEffectsAtActor(this);

    Super::Destroyed();
}

void AGGFSimpleTurret::OnDead_Implementation()
{
    Super::OnDead_Implementation();

    Destroy();
}

bool AGGFSimpleTurret::Activate_Implementation(AActor* InstigatorActor)
{
    // 중복 호출 방지
    if(bActive) return false;
    bActive = true;

    // 애니메이션 활성화
    if(auto AnimInstance = GetSkeletalMesh()->GetAnimInstance())
    {
        if(AnimInstance->Implements<UGGFActivatableInterface>())
        {
            Execute_Activate(AnimInstance, this);
        }
    }

    // 활성화 타이머 설정
    if(ActivationTime <= 0)
    {
        OnActivated();
    }
    else
    {
        auto& TimerManager = GetWorldTimerManager();
        TimerManager.SetTimer(ActivationTimer, this, &ThisClass::OnActivated, ActivationTime);
    }

    return true;
}

bool AGGFSimpleTurret::Deactivate_Implementation(AActor* InstigatorActor)
{
    // 중복 호출 방지
    if(!bActive) return false;
    bActive = false;

    // 애니메이션 비활성화
    if(auto AnimInstance = GetSkeletalMesh()->GetAnimInstance())
    {
        if(AnimInstance->Implements<UGGFActivatableInterface>())
        {
            Execute_Deactivate(AnimInstance, this);
        }
    }

    // 비활성화
    OnDeactivated();

    return true;
}

void AGGFSimpleTurret::OnActivated_Implementation()
{
    auto& TimerManager = GetWorldTimerManager();
    if(HasAuthority())
    {
        TimerManager.SetTimer(AutoFireTimer, GetProjectileSpawner(), &UGGFProjectileSpawner::FireForward, 60 / RPM, true, 0);
    }

}

void AGGFSimpleTurret::OnDeactivated_Implementation()
{
    auto& TimerManager = GetWorldTimerManager();
    if(TimerManager.IsTimerActive(ActivationTimer)) TimerManager.ClearTimer(ActivationTimer);
    if(TimerManager.IsTimerActive(AutoFireTimer)) TimerManager.ClearTimer(AutoFireTimer);
}
