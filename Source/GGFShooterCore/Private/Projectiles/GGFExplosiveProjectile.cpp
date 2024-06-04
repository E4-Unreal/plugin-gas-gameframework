// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectiles/GGFExplosiveProjectile.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"
#include "GEBlueprintFunctionLibrary.h"
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

void AGGFExplosiveProjectile::ApplyEffects(AActor* Target)
{
    if(HasAuthority())
    {
        // 데미지 및 추가 GE 적용
        if(GetInstigator())
        {
            UGEBlueprintFunctionLibrary::ApplyRadialDamageToTarget(GetInstigator(), Target, this, DamageClass, FixedDamage, DamageType.Tag);
            UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToTarget(AdditionalEffects, GetInstigator(), Target);
        }
        else
        {
            UGEBlueprintFunctionLibrary::ApplyRadialDamageToSelf(Target, this, DamageClass, FixedDamage, DamageType.Tag);
            UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToSelf(AdditionalEffects, Target);
        }
    }
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
    for (AActor* OverlappingActor : OverlappingActors)
    {
        if(OverlappingActor == this) continue;
        ApplyEffects(OverlappingActor);
    }
}
