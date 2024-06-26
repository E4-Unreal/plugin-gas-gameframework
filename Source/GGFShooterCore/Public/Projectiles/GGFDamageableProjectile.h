// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFCoreSetting.h"
#include "GGFProjectile.h"
#include "GGFDamageableProjectile.generated.h"

UCLASS()
class GGFSHOOTERCORE_API AGGFDamageableProjectile : public AGGFProjectile
{
    GENERATED_BODY()

public:
    // 데미지 전용 게임플레이 이펙트 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|DamageableProjectile")
    TSubclassOf<UGameplayEffect> DamageClass;

    // 추가로 적용할 게임플레이 이펙트 클래스 목록
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|DamageableProjectile")
    TArray<TSubclassOf<UGameplayEffect>> AdditionalEffects;

    // 데미지 계산식에 영향을 받지 않는 고정 데미지
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|DamageableProjectile")
    float Damage;

    // 데미지 타입
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|DamageableProjectile")
    FGGFDamageTypeTag DamageType;

    // 데미지 배율 (샷건 등에서 사용)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|DamageableProjectile", meta = (ClampMin = 0))
    float DamageRatio = 1;

public:
    AGGFDamageableProjectile(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    /* Projectile */

    virtual void OnSphereColliderHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

    /* 메서드 */

    // 대상에게 데미지 및 추가 GE 적용
    UFUNCTION(BlueprintCallable)
    virtual void ApplyEffects(AActor* Target);
};
