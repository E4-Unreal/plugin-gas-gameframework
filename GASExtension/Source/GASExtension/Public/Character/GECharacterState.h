// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEState.h"
#include "GECharacterState.generated.h"

/**
 * 캐릭터 전용 상태 클래스입니다.
 */
UCLASS()
class GASEXTENSION_API UGECharacterState : public UGEState
{
    GENERATED_BODY()

    TWeakObjectPtr<ACharacter> Character;

protected:
    virtual void OnInit_Implementation() override;

    /* Getter */
    UFUNCTION(BlueprintPure)
    FORCEINLINE ACharacter* GetCharacter() const { return Character.Get(); }
};
