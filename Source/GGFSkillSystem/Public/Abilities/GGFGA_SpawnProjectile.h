// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGA_SpawnActor.h"
#include "GGFGA_SpawnProjectile.generated.h"

class ASkeletalMeshActor;

/**
 * 특수 무기를 꺼내 특수 총알을 발사하는 스킬 어빌리티 클래스입니다.
 */
UCLASS()
class GGFSKILLSYSTEM_API UGGFGA_SpawnProjectile : public UGGFGA_SpawnActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TObjectPtr<USkeletalMesh> SpecialWeaponMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName WeaponSocketName = "weapon_r";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName MuzzleSocketName = "muzzle";

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<ASkeletalMeshActor> SpawnedSpecialWeapon;

    TWeakObjectPtr<AActor> SelectedWeapon;

public:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
    virtual void SpawnSpecialWeapon();

    virtual void HideSelectedWeapon(bool bHide);

    virtual void SpawnActor() override;
};
