// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GECharacterMovementBase.generated.h"

class UAbilitySystemComponent;

/*
 * 캐릭터 무브먼트에 따라 상태 태그가 자동으로 부착됩니다.
 */
UCLASS()
class GASEXTENSION_API UGECharacterMovementBase : public UCharacterMovementComponent
{
    GENERATED_BODY()

protected:
    TWeakObjectPtr<UAbilitySystemComponent> OwnerAbilitySystem;

    UPROPERTY(EditAnywhere, Category = "Config")
    FGameplayTag FallingTag;

    UPROPERTY(EditAnywhere, Category = "Config")
    FGameplayTag CrouchingTag;

public:
    UGECharacterMovementBase();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* CharacterMovementComponent */

    virtual void SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode) override;

    virtual void Crouch(bool bClientSimulation) override;

    virtual void UnCrouch(bool bClientSimulation) override;
};
