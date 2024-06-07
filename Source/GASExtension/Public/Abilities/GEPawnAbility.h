// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEGameplayAbility.h"
#include "GEPawnAbility.generated.h"

/**
 * Pawn 전용 어빌리티 클래스
 */
UCLASS()
class GASEXTENSION_API UGEPawnAbility : public UGEGameplayAbility
{
    GENERATED_BODY()

    TWeakObjectPtr<APawn> AvatarPawn;

public:
    /* GameplayAbility */

    virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

protected:
    UFUNCTION(BlueprintPure)
    FORCEINLINE APawn* GetAvatarPawn() const { return AvatarPawn.Get(); }
};
