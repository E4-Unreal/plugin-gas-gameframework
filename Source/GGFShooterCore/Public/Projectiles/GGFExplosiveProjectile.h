// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDamageableProjectile.h"
#include "GGFExplosiveProjectile.generated.h"

/*
 * 일정 시간이 지나면 자동으로 활성화되는 발사체 클래스입니다.
 * 수류탄 등에서 사용할 수 있습니다.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GGFSHOOTERCORE_API AGGFExplosiveProjectile : public AGGFDamageableProjectile
{
    GENERATED_BODY()

    /* 컴포넌트 */
    UPROPERTY(VisibleAnywhere, Category = "Component")
    TObjectPtr<USphereComponent> ExplosionArea;

protected:
    // 폭발 효과 전용 게임플레이 큐 태그
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|ExplosiveProjectile")
    FGameplayCueTag ExplosionCueTag;

public:
    AGGFExplosiveProjectile();

    /* Actor */

    virtual void Destroyed() override;

protected:

    /* Projectile */

    virtual void OnSphereColliderHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
    virtual void AutoDestroy() override;
    virtual void ApplyEffects(AActor* Target) override;

    /* 메서드 */

    UFUNCTION(BlueprintNativeEvent)
    void Explode();

    // 폭발 효과 스폰
    UFUNCTION(BlueprintCallable)
    virtual void LocalHandleExplosionGameplayCue();

    // ExplosionArea에 오버랩된 액터에 대한 데미지 적용
    UFUNCTION(BlueprintNativeEvent)
    void CheckExplosionArea();
};
