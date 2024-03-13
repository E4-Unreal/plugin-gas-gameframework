// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GECharacterBase.generated.h"

class UGEAbilitySystemBase;
class UGEStateMachine;

/*
 * GEAbilitySystemBase, GEStateMachine을 서브 오브젝트로 가집니다.
 */
UCLASS()
class GASEXTENSION_API AGECharacterBase : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    /* AbilitySystem Component의 이름으로 다른 클래스로 교체할 때 사용합니다. */
    static FName AbilitySystemComponentName;

    /* StateMachine의 이름으로 다른 클래스로 교체할 때 사용합니다. */
    static FName StateMachineName;

private:
    // GAS를 사용하기 위한 ASC입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UGEAbilitySystemBase> AbilitySystem;

    // 캐릭터 상태를 관리하기 위한 컴포넌트입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UGEStateMachine> StateMachine;

public:
    AGECharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Getter */
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintPure, Category = "GECharacterBase")
    FORCEINLINE UGEAbilitySystemBase* GetAbilitySystem() const { return AbilitySystem; }

    UFUNCTION(BlueprintPure, Category = "GECharacterBase")
    FORCEINLINE UGEStateMachine* GetStateMachine() const { return StateMachine; }
};
