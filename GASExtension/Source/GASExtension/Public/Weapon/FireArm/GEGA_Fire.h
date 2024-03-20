// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GEGameplayAbilityBase.h"
#include "GEGA_Fire.generated.h"

class AGEFireArm;

/**
 *
 */
UCLASS()
class GASEXTENSION_API UGEGA_Fire : public UGEGameplayAbilityBase
{
    GENERATED_BODY()

    TWeakObjectPtr<AGEFireArm> CachedFireArm;
    FTimerHandle FireTimer;

public:
    UGEGA_Fire();

protected:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
    UFUNCTION()
    void OnRelease_Event(float TimeHeld);
};
