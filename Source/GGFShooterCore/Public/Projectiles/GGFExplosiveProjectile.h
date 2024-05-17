// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFProjectile.h"
#include "GGFExplosiveProjectile.generated.h"

class UParticleSystem;
class UNiagaraSystem;
class USoundCue;

// TODO 리팩토링
/*
 * 수류탄, 로켓 런처 등 폭발성 투사체 클래스입니다.
 * 클래스 계층 구조가 변경될 수 있으니 유의바랍니다.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GGFSHOOTERCORE_API AGGFExplosiveProjectile : public AGGFProjectile
{
    GENERATED_BODY()

    /* 컴포넌트 */
    UPROPERTY(VisibleAnywhere, Category = "Component")
    TObjectPtr<USphereComponent> ExplosionSphere;

    // 충격 시 폭발 기능 활성화 옵션입니다.
    UPROPERTY(EditAnywhere, Category = "Config|ExplosiveProjectile")
    bool bEnableHit = true;

    // EnableHit이 true로 설정된 경우 DelayTime 이후 폭발합니다.
    UPROPERTY(EditAnywhere, Category = "Config|ExplosiveProjectile")
    float DelayTime = 0;

    FTimerHandle DelayTimer;

    // 피격 여부와 관계없이 ExplosionTime 시간 이후 자동으로 폭발합니다.
    // 0초로 설정한 경우 이 옵션은 비활성화 처리됩니다.
    UPROPERTY(EditAnywhere, Category = "Config|ExplosiveProjectile")
    float ExplosionTime = 0;

    FTimerHandle ExplosionTimer;

    // TODO 데이터 에셋으로 분리?
    UPROPERTY(EditAnywhere, Category = "Config|ExplosiveProjectile")
    TObjectPtr<UParticleSystem> ExplosionParticle;

    UPROPERTY(EditAnywhere, Category = "Config|ExplosiveProjectile")
    TObjectPtr<UNiagaraSystem> ExplosionNiagara;

    UPROPERTY(EditAnywhere, Category = "Config|ExplosiveProjectile")
    TObjectPtr<USoundCue> ExplosionSound;

    UPROPERTY(EditAnywhere, Category = "Config|ExplosiveProjectile")
    TEnumAsByte<ECollisionChannel> CollisionChannel = ECC_WorldDynamic;

public:
    AGGFExplosiveProjectile();

    virtual void BeginPlay() override;

protected:
    virtual void OnComponentHit_Event_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

    UFUNCTION(BlueprintNativeEvent)
    void OnExplode();

    UFUNCTION(NetMulticast, Reliable)
    void OnMulticastExplode();

    UFUNCTION(BlueprintNativeEvent)
    void DetectExplosionHit();

    // 타깃 액터 콜라이더의 Center, Top, Bottom, Left, Right 위치 반환
    // 폭발 피격 판정에 사용됩니다.
    UFUNCTION(BlueprintCallable)
    void GetTargetLocations(const AActor* Target, TArray<FVector>& TargetLocations);
};
