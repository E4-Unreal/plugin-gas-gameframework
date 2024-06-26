// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFPawnAbility.h"
#include "GGFCharacterAbility.generated.h"

/**
 * Character 전용 어빌리티 클래스
 */
UCLASS()
class GGFCORE_API UGGFCharacterAbility : public UGGFPawnAbility
{
    GENERATED_BODY()

    TWeakObjectPtr<ACharacter> AvatarCharacter;

public:
    /* GameplayAbility */

    virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

protected:
    UFUNCTION(BlueprintPure)
    FORCEINLINE ACharacter* GetAvatarCharacter() const { return AvatarCharacter.Get(); }
};
