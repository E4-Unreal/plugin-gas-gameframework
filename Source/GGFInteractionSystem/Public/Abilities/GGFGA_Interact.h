// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GEPlayerAbility.h"
#include "GGFGA_Interact.generated.h"

/**
 * 상호작용을 위한 게임플레이 어빌리티
 */
UCLASS()
class GGFINTERACTIONSYSTEM_API UGGFGA_Interact : public UGEPlayerAbility
{
    GENERATED_BODY()

protected:
    TWeakObjectPtr<AActor> InteractableActor;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    float MaxDistance = 1000;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    float SphereRadius = 20;

#if WITH_EDITORONLY_DATA
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    bool bShowDebug;
#endif

public:
    UGGFGA_Interact();

    /* GameplayAbility */

    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
    virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
    virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

protected:
    virtual void ActivateInteractableObject(bool bActive);

    UFUNCTION()
    virtual void OnInteractableActorDetected_Event(AActor* NewInteractableActor);
};
