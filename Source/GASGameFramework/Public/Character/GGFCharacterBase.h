// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GGFCharacterBase.generated.h"

class UGGFInputManager;
class UGGFStateMachine;
class UAbilitySystemComponent;
class UInputMappingContext;
class UGGFEquipmentManager;

/*
 * 액터 컴포넌트 등록 전용
 */
UCLASS()
class GASGAMEFRAMEWORK_API AGGFCharacterBase : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    /* AbilitySystem Component의 이름으로 다른 클래스로 교체할 때 사용합니다. */
    static FName AbilitySystemComponentName;

    /* InputManager의 이름으로 다른 클래스로 교체할 때 사용합니다. */
    static FName InputManagerName;

    /* EquipmentManager의 이름으로 다른 클래스로 교체할 때 사용합니다. */
    static FName EquipmentManagerName;

    /* EquipmentManager의 이름으로 다른 클래스로 교체할 때 사용합니다. */
    static FName StateMachineName;

private:
    /* 컴포넌트 */
    // GAS를 사용하기 위한 ASC
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAbilitySystemComponent> AbilitySystem;

    // 어빌리티 전용 입력 바인딩을 위한 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UGGFInputManager> InputManager;

    // 장비를 관리하기 위한 컴포넌트입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UGGFEquipmentManager> EquipmentManager;

    // 장비를 관리하기 위한 컴포넌트입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UGGFStateMachine> StateMachine;

public:
    AGGFCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Pawn */
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    /* Character */
    // 앉은 상태에서 점프가 가능하도록 설정
    virtual bool CanJumpInternal_Implementation() const override;

    // 점프 상태에서 앉기가 불가능하도록 설정
    virtual bool CanCrouch() const override;

protected:
    // 향상된 입력 컴포넌트 설정
    virtual void SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent);

public:
    /* AbilitySystemInterface */
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; }
};
