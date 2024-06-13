// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFFireArmAbility.h"
#include "GGFGA_Fire.generated.h"

class AGGFFireArm;
class UAnimMontage;

/**
 * 총기 발사 전용 어빌리티
 */
UCLASS()
class GGFSHOOTERCORE_API UGGFGA_Fire : public UGGFFireArmAbility
{
    GENERATED_BODY()

protected:
    FTimerHandle FireTimer;

public:
    UGGFGA_Fire();

    /* GameplayAbility */

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
    /* GEGameplayAbility */

    virtual bool InternalCanActivate() override;

    /* 메서드 */

    virtual void StopFire();
};
