// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GEPlayerAbility.h"
#include "GGFPA_Sprint.generated.h"

// TODO 게임플레이 이펙트 연동
/**
 * 캐릭터의 빠른 달리기를 위한 플레이어 어빌리티
 */
UCLASS()
class GGFCHARACTERSYSTEM_API UGGFPA_Sprint : public UGEPlayerAbility
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    float MoveSpeedRatio = 1.5f;

    float DefaultMaxWalkSpeed;

public:
    UGGFPA_Sprint();

    /* GameplayAbility */

    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

};
