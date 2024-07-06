// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/GGFActivatableInterface.h"
#include "Pawns/GGFPawn.h"
#include "GGFSimpleTurret.generated.h"

class UCapsuleComponent;
class UGGFProjectileSpawner;
class UGGFEffectManager;

/**
 * 일정 시간마다 총알을 발사하는 기본적인 터렛 액터 클래스입니다.
 */
UCLASS()
class GGFSHOOTERCORE_API AGGFSimpleTurret : public AGGFPawn, public IGGFActivatableInterface
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCapsuleComponent, Category = "Component")
    TObjectPtr<UCapsuleComponent> CapsuleComponent;

    // 터렛 메시
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetSkeletalMesh, Category = "Component")
    TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

    // 총알 스폰을 위한 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetProjectileSpawner, Category = "Component")
    TObjectPtr<UGGFProjectileSpawner> ProjectileSpawner;

    // 파괴 시 폭발 이펙트 재생을 위한 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetEffectManager, Category = "Component")
    TObjectPtr<UGGFEffectManager> EffectManager;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float RPM = 60;

    FTimerHandle AutoFireTimer;

    // 자동 활성화 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bAutoActivate;

    // 활성화 여부
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, ReplicatedUsing = OnRep_Active)
    bool bActive = false;

    // 활성화 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float ActivationTime = 2.5f;

    FTimerHandle ActivationTimer;

    // 비활성화 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float DeactivationTime = 2.5f;

    FTimerHandle DeactivationTimer;

public:
    AGGFSimpleTurret(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void BeginPlay() override;
    virtual void Destroyed() override;
    virtual void LifeSpanExpired() override;

    /* GGFPawn */

    virtual void OnDead_Implementation() override;

    /* ActivatableInterface */

    virtual bool TryActivate_Implementation(AActor* InCauser, AActor* InInstigator) override;
    virtual bool TryDeactivate_Implementation(AActor* InCauser, AActor* InInstigator) override;

protected:
    /* 이벤트 */

    UFUNCTION(BlueprintNativeEvent, Category = "Event")
    void OnActivated();

    UFUNCTION(BlueprintNativeEvent, Category = "Event")
    void OnDeactivated();

    /* 리플리케이트 */

    UFUNCTION()
    virtual void OnRep_Active(bool bOldActive);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USkeletalMeshComponent* GetSkeletalMesh() const { return SkeletalMesh; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFProjectileSpawner* GetProjectileSpawner() const { return ProjectileSpawner; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFEffectManager* GetEffectManager() const { return EffectManager; }
};
