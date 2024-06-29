// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFPawnState.h"
#include "GGFCharacterState.generated.h"

/**
 * 캐릭터 전용 게임플레이 스테이트 클래스
 */
UCLASS(HideDropdown)
class GGFCORE_API UGGFCharacterState : public UGGFPawnState
{
    GENERATED_BODY()

    /* 레퍼런스 */

    TWeakObjectPtr<ACharacter> OwnerCharacter;

public:
    virtual void SetOwner(AActor* NewOwner) override;

protected:
    UFUNCTION(BlueprintPure)
    FORCEINLINE ACharacter* GetOwnerCharacter() const { return OwnerCharacter.Get(); }
};
