// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueInterface.h"
#include "GameFramework/Actor.h"
#include "GGFProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UGameplayEffect;
class UGGFHitEffectDefinition;

/*
 * 충격이 가해지는 즉시 활성화되는 기본 발사체 클래스입니다.
 * ex) 총알, 로켓, 충격 수류탄 등
 */
UCLASS(BlueprintType, Blueprintable)
class GGFSHOOTERCORE_API AGGFProjectile : public AActor
{
    GENERATED_BODY()

public:
    /* 서브 오브젝트 이름 */

    static FName ProjectileMovementName;

private:
    /* 컴포넌트 */

    // 피격 판정
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetSphereCollider, Category = "Component")
    TObjectPtr<USphereComponent> SphereCollider;

    // 시각 요소
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDisplayMesh, Category = "Component")
    TObjectPtr<UStaticMeshComponent> DisplayMesh;

    // 이동
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetProjectileMovement, Category = "Component")
    TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

protected:
    // SphereCollider::OnComponentHit 이벤트 바인딩 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Projectile")
    bool bEnableHitTrigger = true;

    // 물체에 충돌하지 않더라도 자동으로 파괴되는 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Projectile")
    float AutoDestroyTime = 10;

    FTimerHandle AutoDestroyTimer;

    // 피격 혹은 바운스 효과 전용 게임플레이 큐 태그
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Projectile")
    FGameplayCueTag HitCueTag;

    // OnProjectileMovementBounce가 동작하기 위한 최소 ImpactResult.Distance
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Projectile")
    float BounceThreshold = 2;

public:
    AGGFProjectile(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void PostInitializeComponents() override;
    virtual void BeginPlay() override;
    virtual void Destroyed() override;

protected:
    /* 메서드 */

    // 파괴 전 불필요한 기능을 정지하는 메서드입니다.
    UFUNCTION(BlueprintNativeEvent)
    void Deactivate();

    // 자동 파괴 타이머 설정
    UFUNCTION(BlueprintCallable)
    virtual void SetAutoDestroyTimer();

    // 리플리케이트 혹은 이펙트 종료 대기 등의 목적을 위해 파괴를 지연시키는 메서드입니다.
    UFUNCTION(BlueprintCallable)
    virtual void DestroyDeferred();

    // 피격 효과 스폰
    UFUNCTION(BlueprintCallable)
    virtual void LocalHandleHitGameplayCue(const FHitResult& HitResult, const FGameplayTag& EffectTag) const;

    // SphereCollider::OnComponentHit 이벤트 메서드
    UFUNCTION(BlueprintNativeEvent, Category = "Event")
    void OnSphereColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    // ProjectileMovement::OnProjectileBounce 이벤트 메서드
    UFUNCTION(BlueprintNativeEvent, Category = "Event")
    void OnProjectileMovementBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);

public:
    /* Getter */
    UFUNCTION(BlueprintGetter)
    FORCEINLINE USphereComponent* GetSphereCollider() const { return SphereCollider; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UStaticMeshComponent* GetDisplayMesh() const { return DisplayMesh; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
