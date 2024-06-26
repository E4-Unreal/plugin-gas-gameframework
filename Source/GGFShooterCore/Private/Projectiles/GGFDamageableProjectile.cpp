// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectiles/GGFDamageableProjectile.h"

#include "GEBlueprintFunctionLibrary.h"
#include "GGFBlueprintFunctionLibrary.h"
#include "GameplayEffects/GEDamageBase.h"
#include "GGFGameplayTags.h"



AGGFDamageableProjectile::AGGFDamageableProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    DamageClass = UGEDamageBase::StaticClass();
    FixedDamage = 10;
    DamageType = Damage::Type::Default;
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
            UGEBlueprintFunctionLibrary::ApplyDamageToTarget(GetInstigator(), Target, DamageClass, FixedDamage, DamageRatio, DamageType.Tag);
            UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToTarget(GetInstigator(), Target, AdditionalEffects);
        }
        else
        {
            UGEBlueprintFunctionLibrary::ApplyDamageToSelf(Target, DamageClass, FixedDamage, DamageRatio, DamageType.Tag);
            UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToSelf(Target, AdditionalEffects);
        }
    }
}
