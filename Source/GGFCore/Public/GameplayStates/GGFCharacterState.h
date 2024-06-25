// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGameplayState.h"
#include "GGFCharacterState.generated.h"

/**
 * 캐릭터 전용 GameplayEventAction 클래스입니다.
 */
UCLASS(HideDropdown)
class GGFCORE_API UGGFCharacterState : public UGGFGameplayState
{
    GENERATED_BODY()

    TWeakObjectPtr<ACharacter> OwnerCharacter;

public:
    virtual void SetOwner(AActor* NewOwner) override;

protected:
    UFUNCTION(BlueprintPure)
    FORCEINLINE ACharacter* GetOwnerCharacter() const { return OwnerCharacter.Get(); }
};
