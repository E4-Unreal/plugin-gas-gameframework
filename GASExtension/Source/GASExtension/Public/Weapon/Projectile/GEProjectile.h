// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GEProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UGameplayEffect;
class UGEHitEffectDefinition;

// TODO 아직 테스트 단계로 클래스 구조 및 API가 변경될 수 있습니다.
/*
 * 총알, 로켓, 수류탄 등 발사체 및 투척물에 사용되는 기본 클래스로 OnHit과 OnMulticastHit을 오버라이드하시면 됩니다.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
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

protected:
#if WITH_EDITORONLY_DATA
  UPROPERTY(EditAnywhere, Category = "Config|Projectile")
    bool bShowDebug;
#endif

    // TODO EffectsToApply, HitEffect를 묶어 액터 컴포넌트로 추출 고려
    // 피격 대상에게 적용할 GameplayEffect 목록입니다. 데미지 관련 GameplayEffect 역시 이곳에 포함됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Projectile")
    TArray<TSubclassOf<UGameplayEffect>> EffectsToApply;

    // 피격 효과
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Projectile")
    TObjectPtr<UGEHitEffectDefinition> HitEffect;

public:
    AGEProjectile();

    /* Actor */
    virtual void PostInitializeComponents() override;

protected:
    /* 이벤트 핸들러 */
    UFUNCTION(BlueprintNativeEvent)
    void OnComponentHit_Event(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    /* 가상 메서드 */
    UFUNCTION(BlueprintNativeEvent)
    void OnHit(const FHitResult& HitResult);

    UFUNCTION(NetMulticast, Reliable)
    void OnMulticastHit(const FHitResult& HitResult);

public:
    /* Getter */
    UFUNCTION(BlueprintGetter)
    FORCEINLINE USphereComponent* GetSphereCollider() const { return SphereCollider; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
