// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueInterface.h"
#include "GGFCore/Public/Components/GGFActorComponent.h"
#include "GGFProjectileSpawner.generated.h"

class AGGFProjectile;

/**
 * 발사체를 스폰하는 기능이 구현된 액터 컴포넌트
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFSHOOTERCORE_API UGGFProjectileSpawner : public UGGFActorComponent
{
    GENERATED_BODY()

public:
    // 총구 소켓 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName MuzzleSocketName = "Muzzle";

    // 발사할 발사체 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<AGGFProjectile> ProjectileClass;

    // 발사체 스폰 시 총구에서 재생할 게임플레이 큐 태그
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGameplayCueTag MuzzleCueTag;

private:
    TWeakObjectPtr<USkeletalMeshComponent> SkeletalMesh;

public:
    UGGFProjectileSpawner();

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void Init(USkeletalMeshComponent* InSkeletalMesh);

    UFUNCTION(BlueprintCallable)
    virtual void FireForward();

    UFUNCTION(BlueprintCallable)
    virtual void FireToTarget(const FVector& TargetLocation);

protected:
    UFUNCTION(BlueprintCallable)
    virtual AGGFProjectile* SpawnProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation);

    UFUNCTION(BlueprintCallable)
    virtual void PlayMuzzleGameplayCue(const FVector& SpawnLocation, const FRotator& SpawnRotation);

public:
    /* Getter */

    UFUNCTION(BlueprintPure)
    FORCEINLINE USkeletalMeshComponent* GetSkeletalMesh() const { return SkeletalMesh.Get(); }
};
