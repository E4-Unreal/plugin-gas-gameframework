// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEGA_AutoActivatable.h"
#include "GEGA_ApplyEffectsToSelf.generated.h"

/**
 * Ability를 발동한 주체에게 GameplayEffects를 적용하는 Ability입니다.
 * AttributeSet 초기화, 아이템 효과 적용 등을 위해 사용할 수 있습니다.
 * 사용 방법은 적용할 대상에게 GiveAbility로 전달하면 됩니다.
 */
UCLASS()
class GASEXTENSION_API UGEGA_ApplyEffectsToSelf : public UGEGA_AutoActivatable
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<TSubclassOf<UGameplayEffect>> EffectsToApply;

public:
    /* UGameplayAbility */

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
