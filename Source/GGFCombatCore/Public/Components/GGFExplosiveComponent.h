// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueInterface.h"
#include "GASExtensionSetting.h"
#include "Components/ActorComponent.h"
#include "GGFExplosiveComponent.generated.h"

class USphereComponent;
class UAbilitySystemComponent;
class UGameplayEffect;

// TODO CollisionChannel 대신 BlockingChannel 설정으로 대체 필요
/**
 * 폭발 피격 판정 전용 컴포넌트
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFCOMBATCORE_API UGGFExplosiveComponent : public UActorComponent
{
    GENERATED_BODY()

    TWeakObjectPtr<USphereComponent> ExplosionArea;

public:
    // 폭발 데미지 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|ExplosiveComponent")
    TSubclassOf<UGameplayEffect> DamageEffect;

    // 폭발 범위 대상에게 적용할 추가 이펙트
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|ExplosiveComponent")
    TArray<TSubclassOf<UGameplayEffect>> AdditionalEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|ExplosiveComponent")
    float FixedDamage = 50;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|ExplosiveComponent")
    FDamageTypeTag DamageType;

    // 폭발 피격 판정을 위한 콜리전 채널
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|ExplosiveComponent")
    TEnumAsByte<ECollisionChannel> CollisionChannel = ECC_WorldDynamic;

    // 거리에 따른 데미지 배율 감소가 적용되지 않는 최대 범위 비율로 1인 경우 모든 범위에서 동일한 데미지가 적용됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|ExplosiveComponent", meta = (ClampMin = 0, ClampMax = 1))
    float InnerRadiusRatio = 1;

    // 폭발 이펙트 전용 게임플레이 큐 태그
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|ExplosiveComponent")
    FGameplayCueTag ExplosionCueTag;

    // 폭발 후 자동 파괴 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|ExplosiveComponent")
    bool bAutoDestroy = true;

protected:
#if WITH_EDITORONLY_DATA
    UPROPERTY(VisibleAnywhere, Category = "Config|ExplosiveComponent|Debug")
    bool bValid = false;

    UPROPERTY(EditAnywhere, Category = "Config|ExplosiveComponent|Debug")
    bool bShowDebug = false;
#endif

public:
    UGGFExplosiveComponent();

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void Init(USphereComponent* InExplosionArea);

    UFUNCTION(BlueprintCallable)
    virtual void Explode();

protected:
    /* 메서드 */

    // ApplyRadialDamage를 위한 데미지 배율 계산
    virtual float CalculateDamageRatio(AActor* Target);

    // TODO 피격판정 로직 개선 필요
    // 폭발 피격 판정을 위한 위치 계산
    static void GetLocationsForExplosionDetection(AActor* Target, TArray<FVector>& TargetLocations);

    // 폭발 피격 대상에게 데미지 및 추가 효과 적용
    UFUNCTION(BlueprintCallable)
    virtual void ApplyEffects(AActor* Target);
};
