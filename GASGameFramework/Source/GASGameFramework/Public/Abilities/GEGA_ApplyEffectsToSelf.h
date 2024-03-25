// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEGameplayAbility.h"
#include "GEGA_ApplyEffectsToSelf.generated.h"

/**
 * Ability를 발동한 주체에게 GameplayEffects를 적용하는 Ability입니다.
 * 힐이나 버프같은 간단한 스킬 구현에 사용할 수 있습니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGEGA_ApplyEffectsToSelf : public UGEGameplayAbility
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<TSubclassOf<UGameplayEffect>> EffectsToApply;

public:
    /* UGameplayAbility */

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
