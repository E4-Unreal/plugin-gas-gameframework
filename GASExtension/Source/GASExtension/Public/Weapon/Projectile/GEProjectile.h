// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GEProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UGameplayEffect;
class UGEHitEffectDefinition;

/*
 * 총알, 로켓, 수류탄 등 발사체 및 투척물에 사용되는 기본 클래스입니다.
 */
UCLASS(Abstract)
class GASEXTENSION_API AGEProjectile : public AActor
{
    GENERATED_BODY()

    /* 컴포넌트 */

    // 피격 판정
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetSphereCollider, Category = "Component")
    TObjectPtr<USphereComponent> SphereCollider;

    // 이동
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetProjectileMovement, Category = "Component")
    TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

    // TODO EffectsToApply, HitEffect를 묶어 액터 컴포넌트로 추출 고려
    // 피격 대상에게 적용할 GameplayEffect 목록입니다. 데미지 관련 GameplayEffect 역시 이곳에 포함됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Projectile", meta = (AllowPrivateAccess = true))
    TArray<TSubclassOf<UGameplayEffect>> EffectsToApply;

    // 피격 효과
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Projectile", meta = (AllowPrivateAccess = true))
    TObjectPtr<UGEHitEffectDefinition> HitEffect;

public:
    AGEProjectile();

    /* Actor */
    virtual void PostInitializeComponents() override;

protected:
    /* 가상 메서드 */
    UFUNCTION(BlueprintNativeEvent)
    void OnHit(const FHitResult& HitResult);

    UFUNCTION(NetMulticast, Reliable)
    void OnMulticastHit(const FHitResult& HitResult);

private:
    /* 이벤트 핸들러 */
    UFUNCTION()
    void OnComponentHit_Event(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
    /* Getter */
    UFUNCTION(BlueprintGetter)
    FORCEINLINE USphereComponent* GetSphereCollider() const { return SphereCollider; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
