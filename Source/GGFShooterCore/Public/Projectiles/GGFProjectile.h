// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGFProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UGGFEffectManager;

/*
 * 충격이 가해지는 즉시 활성화되는 기본 발사체 클래스입니다.
 * ex) 총알, 로켓, 충격 수류탄 등
 */
UCLASS(BlueprintType, Blueprintable)
class GGFSHOOTERCORE_API AGGFProjectile : public AActor
{
    GENERATED_BODY()

public:
    /* 컴포넌트 이름 */

    static FName ProjectileMovementName;
    static FName EffectManagerName;

private:
    /* 컴포넌트 */

    // 피격 판정을 위한 콜라이더
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetSphereCollider, Category = "Component")
    TObjectPtr<USphereComponent> SphereCollider;

    // 발사체 메시
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDisplayMesh, Category = "Component")
    TObjectPtr<UStaticMeshComponent> DisplayMesh;

    // 발사체 이동 전용 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetProjectileMovement, Category = "Component")
    TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

    // 이펙트 스폰 전용 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetEffectManager, Category = "Component")
    TObjectPtr<UGGFEffectManager> EffectManager;

public:
    AGGFProjectile(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void PostInitializeComponents() override;
    virtual void BeginPlay() override;

protected:
    /* 이벤트 */

    UFUNCTION(BlueprintNativeEvent, Category = "Event")
    void OnSphereColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    /* 메서드 */

    // 피격 효과 스폰
    UFUNCTION(NetMulticast, Reliable)
    virtual void NetMulticastSpawnHitEffects(const FHitResult& HitResult);

public:
    /* Getter */
    UFUNCTION(BlueprintGetter)
    FORCEINLINE USphereComponent* GetSphereCollider() const { return SphereCollider; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UStaticMeshComponent* GetDisplayMesh() const { return DisplayMesh; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFEffectManager* GetEffectManager() const { return EffectManager; }
};
