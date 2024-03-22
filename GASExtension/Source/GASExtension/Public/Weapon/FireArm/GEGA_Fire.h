// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GEGA_Montage.h"
#include "GEGA_Fire.generated.h"

class AGEFireArm;
class UAnimMontage;

/**
 * 총기 발사 전용 어빌리티
 */
UCLASS()
class GASEXTENSION_API UGEGA_Fire : public UGEGA_Montage
{
    GENERATED_BODY()

protected:
    TWeakObjectPtr<AGEFireArm> CachedFireArm;
    FTimerHandle FireTimer;

public:
    UGEGA_Fire();

protected:
    /* GameplayAbility */
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
    UFUNCTION()
    void OnRelease_Event(float TimeHeld);
};
