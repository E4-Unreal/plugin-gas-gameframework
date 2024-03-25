// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GEStateAbility.generated.h"

/**
 * 상태 태그의 추가 혹은 제거 이벤트를 트리거로 발동되는 게임플레이 어빌리티입니다.
 */
UCLASS(Abstract)
class GASEXTENSION_API UGEStateAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UGEStateAbility();

    /* GameplayAbility */
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
    UFUNCTION(BlueprintNativeEvent)
    void OnEnter();

    UFUNCTION(BlueprintNativeEvent)
    void OnExit();
};
