// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GECharacter.generated.h"

class UGEInputManager;

UCLASS()
class GASEXTENSION_API AGECharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    /* AbilitySystem의 이름으로 다른 클래스로 교체할 때 사용합니다. */
    static FName AbilitySystemName;

    /* InputManager의 이름으로 다른 클래스로 교체할 때 사용합니다. */
    static FName InputManagerName;

private:
    /* 컴포넌트 */
    // GAS를 사용하기 위한 ASC
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAbilitySystemComponent> AbilitySystem;

    // 어빌리티 전용 입력 바인딩을 위한 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UGEInputManager> InputManager;

public:
    AGECharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Pawn */
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
    // 향상된 입력 컴포넌트 설정
    virtual void SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent);

public:
    /* AbilitySystemInterface */
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; }
};
