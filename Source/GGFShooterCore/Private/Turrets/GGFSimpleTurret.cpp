// Fill out your copyright notice in the Description page of Project Settings.

#include "Turrets/GGFSimpleTurret.h"

#include "Components/CapsuleComponent.h"
#include "Components/GGFProjectileSpawner.h"
#include "Net/UnrealNetwork.h"

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

void AGGFSimpleTurret::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, bActive);
}

void AGGFSimpleTurret::BeginPlay()
{
    Super::BeginPlay();

    if(bAutoActivate && HasAuthority())
    {
        Execute_Activate(this, this);
    }
}

void AGGFSimpleTurret::Destroyed()
{
    // 폭발 효과 스폰
    GetEffectManager()->PlayEffectsAtActor(this);

    Super::Destroyed();
}

void AGGFSimpleTurret::LifeSpanExpired()
{
    Execute_Deactivate(this, this);
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

    // 비활성화 타이머 설정
    if(DeactivationTime <= 0)
    {
        OnDeactivated();
    }
    else
    {
        auto& TimerManager = GetWorldTimerManager();
        TimerManager.SetTimer(DeactivationTimer, this, &ThisClass::OnDeactivated, DeactivationTime);
    }

    return true;
}

void AGGFSimpleTurret::OnRep_Active(bool bOldActive)
{
    bool bNewActive = bActive;
    bActive = bOldActive;

    if(bNewActive) Execute_Activate(this, this);
    else Execute_Deactivate(this, this);
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
    if(TimerManager.IsTimerActive(DeactivationTimer)) TimerManager.ClearTimer(DeactivationTimer);

    Destroy();
}
