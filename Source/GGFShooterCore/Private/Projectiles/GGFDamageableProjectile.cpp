// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectiles/GGFDamageableProjectile.h"

#include "GGFBlueprintFunctionLibrary.h"
#include "GGFGameplayTags.h"
#include "GameplayEffects/GGFStatDamage.h"

AGGFDamageableProjectile::AGGFDamageableProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    DamageEffect = UGGFStatDamage::StaticClass();
    Damage = 10;
    DamageType = Data::Damage::Type::Default;
}

void AGGFDamageableProjectile::OnSphereColliderHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                                                  UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // 피격 대상에게 데미지 및 추가 GE 적용
    ApplyEffects(OtherActor);

    Super::OnSphereColliderHit_Implementation(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}

void AGGFDamageableProjectile::ApplyEffects(AActor* Target)
{
    if(HasAuthority())
    {
        // 데미지 및 추가 GE 적용
        if(GetInstigator())
        {
            UGGFBlueprintFunctionLibrary::ApplyDamageToTarget(GetInstigator(), Target, Damage, DamageRatio, DamageType.Tag, DamageEffect);
            UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToTarget(GetInstigator(), Target, EffectsToApply);
        }
        else
        {
            UGGFBlueprintFunctionLibrary::ApplyDamageToSelf(Target,Damage, DamageRatio, DamageType.Tag, DamageEffect);
            UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToSelf(Target, EffectsToApply);
        }
    }
}
