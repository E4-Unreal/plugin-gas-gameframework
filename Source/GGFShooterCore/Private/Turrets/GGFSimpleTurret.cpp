// Fill out your copyright notice in the Description page of Project Settings.

#include "Turrets/GGFSimpleTurret.h"

#include "Components/GGFProjectileSpawner.h"

AGGFSimpleTurret::AGGFSimpleTurret(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* SkeletalMesh */
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SetRootComponent(SkeletalMesh);
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
    if(bActivated) Execute_Deactivate(this, this);

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
    if(bActivated) return false;
    bActivated = true;

    if(HasAuthority())
    {
        GetWorldTimerManager().SetTimer(AutoFireTimer, GetProjectileSpawner(), &UGGFProjectileSpawner::FireForward, 60 / RPM, true);
    }

    return true;
}

bool AGGFSimpleTurret::Deactivate_Implementation(AActor* InstigatorActor)
{
    if(!bActivated) return false;
    bActivated = false;

    auto& TimerManager = GetWorldTimerManager();
    if(TimerManager.IsTimerActive(AutoFireTimer)) GetWorldTimerManager().ClearTimer(AutoFireTimer);

    return true;
}
