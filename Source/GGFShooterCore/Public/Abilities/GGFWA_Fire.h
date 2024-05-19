// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFFireArmAbility.h"
#include "GGFWA_Fire.generated.h"

class AGGFFireArm;
class UAnimMontage;

/**
 * 총기 발사 전용 어빌리티
 */
UCLASS()
class GGFSHOOTERCORE_API UGGFWA_Fire : public UGGFFireArmAbility
{
    GENERATED_BODY()

protected:
    FTimerHandle FireTimer;

public:
    UGGFWA_Fire();

protected:
    /* GameplayAbility */
    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

    /* 메서드 */
    virtual void StopFire();
};
