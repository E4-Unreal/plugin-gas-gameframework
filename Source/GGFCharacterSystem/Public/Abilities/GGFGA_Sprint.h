// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GGFCharacterAbility.h"
#include "Abilities/GGFGameplayAbility.h"
#include "GGFGA_Sprint.generated.h"

class UCharacterMovementComponent;

// TODO 게임플레이 이펙트 연동
/**
 * 캐릭터의 빠른 달리기를 위한 플레이어 어빌리티
 */
UCLASS()
class GGFCHARACTERSYSTEM_API UGGFGA_Sprint : public UGGFCharacterAbility
{
    GENERATED_BODY()

    TWeakObjectPtr<UCharacterMovementComponent> AvatarCharacterMovement;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    float MoveSpeedRatio = 1.5f;

    float DefaultMaxWalkSpeed = 0;

public:
    UGGFGA_Sprint();

    /* GameplayAbility */

    virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
    /* GameplayAbility */

    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
    UFUNCTION(BlueprintPure)
    FORCEINLINE UCharacterMovementComponent* GetAvatarCharacterMovement() const { return AvatarCharacterMovement.Get(); }
};
