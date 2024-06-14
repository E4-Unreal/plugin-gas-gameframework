// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFFireArmAbility.h"
#include "GGFGA_ADS.generated.h"

class UGGFCameraComponent;

/**
 * 총기 조준을 위한 어빌리티
 */
UCLASS()
class GGFSHOOTERCORE_API UGGFGA_ADS : public UGGFFireArmAbility
{
    GENERATED_BODY()

    TWeakObjectPtr<UGGFCameraComponent> CameraComponent;

public:
    UGGFGA_ADS();

    /* GameplayAbility */

    virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
    UFUNCTION(BlueprintCallable)
    UGGFCameraComponent* GetCameraComponent() const { return CameraComponent.Get(); }
};
