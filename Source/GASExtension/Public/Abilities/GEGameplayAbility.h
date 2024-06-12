// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Interfaces/GEPlayerAbilityInterface.h"
#include "GEGameplayAbility.generated.h"

/**
 * 자주 사용하는 정책과 게임플레이 태그 설정이 적용된 게임플레이 어빌리티 클래스입니다.
 */
UCLASS()
class GASEXTENSION_API UGEGameplayAbility : public UGameplayAbility, public IGEPlayerAbilityInterface
{
    GENERATED_BODY()

protected:
    // Ability InputID로 사용할 게임플레이 태그입니다.
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config", meta = (Categories = "Input"))
    FGameplayTag InputTag;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State", Transient)
    bool bValid = true;

public:
    UGEGameplayAbility();

    /* GameplayAbility */

    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
    virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
    virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

    /* GEPlayerAbilityInterface */

    virtual FORCEINLINE FGameplayTag GetAbilityInputTag_Implementation() const override { return InputTag; }

protected:
    /* GameplayAbility */

    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

    /* 메서드 */

    // 인스턴싱 정책이 InstancedPerActor로 설정된 경우 CanActivateAbility에서 사용됩니다.
    UFUNCTION(BlueprintPure)
    virtual bool InternalCanActivate() { return true; }
};
