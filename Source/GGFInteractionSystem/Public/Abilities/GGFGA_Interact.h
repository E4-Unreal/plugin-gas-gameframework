// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GGFGameplayAbility.h"
#include "GGFGA_Interact.generated.h"

class UGGFInteractionManager;

/**
 * 상호작용을 위한 게임플레이 어빌리티
 */
UCLASS()
class GGFINTERACTIONSYSTEM_API UGGFGA_Interact : public UGGFGameplayAbility
{
    GENERATED_BODY()

    TWeakObjectPtr<UGGFInteractionManager> InteractionManager;

public:
    UGGFGA_Interact();

    /* GameplayAbility */

    virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

    /* GEGameplayAbility */

    virtual bool InternalCanActivate() override;
};
