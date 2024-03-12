// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "GEState.generated.h"

class UGEStateMachine;
/**
 * 상태 머신에서 사용할 상태 클래스입니다.
 * 상태 머신에서 상태를 생성할 때 반드시 Init 메서드를 호출해주어야 합니다.
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew, DefaultConfig)
class GASEXTENSION_API UGEState : public UObject
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true))
    FGameplayTagContainer Triggers;

private:

    TWeakObjectPtr<UGEStateMachine> StateMachine;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true), Transient)
    bool bInitialized;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true), Transient)
    FGameplayTagContainer ActivatedTriggers;

public:
    UFUNCTION(BlueprintCallable)
    void Init(UGEStateMachine* InStateMachine);

    UFUNCTION(BlueprintCallable)
    void Enter(const FGameplayTag& Tag);

    UFUNCTION(BlueprintCallable)
    void Exit(const FGameplayTag& Tag);

    UFUNCTION(BlueprintPure)
    bool IsActivated() const { return ActivatedTriggers.Num() > 0; }

    UFUNCTION(BlueprintPure)
    const FGameplayTagContainer& GetTriggers() const { return Triggers; }

protected:
    UFUNCTION(BlueprintNativeEvent)
    void OnInit();

    UFUNCTION(BlueprintNativeEvent)
    void OnEnter();

    UFUNCTION(BlueprintNativeEvent)
    void OnExit();

    UFUNCTION(BlueprintPure)
    UGEStateMachine* GetStateMachine() const { return StateMachine.Get(); }
};
