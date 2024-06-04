// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDamageableProjectile.h"
#include "GGFExplosiveProjectile.generated.h"

class UGGFExplosiveComponent;

/*
 * 일정 시간이 지나면 자동으로 활성화되는 발사체 클래스입니다.
 * 수류탄 등에서 사용할 수 있습니다.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GGFSHOOTERCORE_API AGGFExplosiveProjectile : public AGGFDamageableProjectile
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetExplosionArea, Category = "Component")
    TObjectPtr<USphereComponent> ExplosionArea;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetExplosiveComponent, Category = "Component")
    TObjectPtr<UGGFExplosiveComponent> ExplosiveComponent;

public:
    AGGFExplosiveProjectile();

    /* Actor */

    virtual void PostInitializeComponents() override;
    virtual void Destroyed() override;

protected:
    /* Projectile */

    virtual void OnSphereColliderHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

protected:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    USphereComponent* GetExplosionArea() const { return ExplosionArea; }

    UFUNCTION(BlueprintGetter)
    UGGFExplosiveComponent* GetExplosiveComponent() const { return ExplosiveComponent; }
};
