// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GECharacterMovement.generated.h"

class UAbilitySystemComponent;

/*
 * 캐릭터 무브먼트에 따라 상태 태그가 자동으로 부착됩니다.
 */
UCLASS()
class GASEXTENSION_API UGECharacterMovement : public UCharacterMovementComponent
{
    GENERATED_BODY()

protected:
    TWeakObjectPtr<UAbilitySystemComponent> OwnerAbilitySystem;

    UPROPERTY(EditAnywhere, Category = "Config")
    FGameplayTag FallingTag;

    UPROPERTY(EditAnywhere, Category = "Config")
    FGameplayTag CrouchingTag;

public:
    UGECharacterMovement();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* CharacterMovementComponent */

    // 점프 혹은 낙하 상태 태그 부착 혹은 제거
    virtual void SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode) override;

    // 앉기 상태 태그 부착
    virtual void Crouch(bool bClientSimulation) override;

    // 앉기 상태 태그 제거
    virtual void UnCrouch(bool bClientSimulation) override;

    // 앉은 상태에서 점프 가능
    virtual bool CanAttemptJump() const override;

    // 앉은 상태에서 점프를 하는 경우 UnCrouch를 먼저 호출
    virtual bool DoJump(bool bReplayingMoves) override;
};
