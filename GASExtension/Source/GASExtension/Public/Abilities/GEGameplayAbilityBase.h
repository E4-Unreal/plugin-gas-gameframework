// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GEGameplayAbilityBase.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class GASEXTENSION_API UGEGameplayAbilityBase : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UGEGameplayAbilityBase();

    /* UGameplayAbility */

    virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

    // true 설정 시 Ability가 부여되는 즉시 해당 Ability를 발동합니다.
    // HitReact처럼 수동적인 Ability에서 사용합니다.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
    bool bActivateAbilityOnGranted = false;
};
