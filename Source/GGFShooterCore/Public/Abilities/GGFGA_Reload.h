// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFFireArmAbility.h"
#include "GGFGA_Reload.generated.h"

/**
 *
 */
UCLASS()
class GGFSHOOTERCORE_API UGGFGA_Reload : public UGGFFireArmAbility
{
    GENERATED_BODY()

public:
    UGGFGA_Reload();

    /* GameplayAbility */

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
    /* GEGameplayAbility */

    virtual bool InternalCanActivate() override;

    UFUNCTION()
    virtual void OnReloadFinished();
};
