// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGameplayState.h"
#include "GGFPawnState.generated.h"

/**
 * 폰 전용 게임플레이 스테이트 클래스
 */
UCLASS(HideDropdown)
class GGFCORE_API UGGFPawnState : public UGGFGameplayState
{
    GENERATED_BODY()

    /* 레퍼런스 */

    TWeakObjectPtr<APawn> OwnerPawn;

public:
    virtual void SetOwner(AActor* NewOwner) override;

protected:
    UFUNCTION(BlueprintPure)
    FORCEINLINE APawn* GetOwnerPawn() const { return OwnerPawn.Get(); }
};
