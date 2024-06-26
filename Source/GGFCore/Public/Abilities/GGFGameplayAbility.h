// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Interfaces/GGFPlayerAbilityInterface.h"
#include "GGFGameplayAbility.generated.h"

/**
 * 자주 사용하는 정책과 게임플레이 태그 설정이 적용된 게임플레이 어빌리티 클래스입니다.
 */
UCLASS()
class GGFCORE_API UGGFGameplayAbility : public UGameplayAbility, public IGGFPlayerAbilityInterface
{
    GENERATED_BODY()

public:
    // Ability InputID로 사용할 게임플레이 태그입니다.
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config", meta = (Categories = "Input"))
    FGameplayTag InputTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Cooldown", meta = (ClampMin = 0))
    float CooldownTime = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Cooldown", meta = (Categories = "Skill.Cooldown"))
    FGameplayTag CooldownTag;

    // 입력 비활성화를 통한 어빌리티 취소 가능 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bCancelableByInputRelease = true;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State", Transient)
    bool bValid = true;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UGameplayEffect> CooldownEffectInstance;

public:
    UGGFGameplayAbility();

    /* GameplayAbility */

    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
    virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
    virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

    virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
    virtual UGameplayEffect* GetCooldownGameplayEffect() const override;

    /* GEPlayerAbilityInterface */

    virtual FORCEINLINE FGameplayTag GetAbilityInputTag_Implementation() const override { return InputTag; }

    /* API */

    virtual void CreateCooldownEffectInstance();

protected:
    /* GameplayAbility */

    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

    /* 메서드 */

    // 인스턴싱 정책이 InstancedPerActor로 설정된 경우 CanActivateAbility에서 사용됩니다.
    UFUNCTION(BlueprintPure)
    virtual bool InternalCanActivate();
};
