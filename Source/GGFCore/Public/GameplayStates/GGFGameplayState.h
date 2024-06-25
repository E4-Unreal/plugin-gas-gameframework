// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "GGFGameplayState.generated.h"

class UAbilitySystemComponent;
/**
 * GameplayStateMachine에서 사용되는 상태 클래스
 */
UCLASS(Blueprintable, BlueprintType, HideDropdown)
class GGFCORE_API UGGFGameplayState : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (Categories = "State"))
    FGameplayTag StateTag;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bValid;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bActivated;

private:
    TWeakObjectPtr<AActor> Owner;

    TWeakObjectPtr<UAbilitySystemComponent> OwnerAbilitySystem;

public:
    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void SetOwner(AActor* NewOwner);

    UFUNCTION(BlueprintPure)
    bool IsValid() const;

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

    UFUNCTION(BlueprintCallable)
    virtual void Enter();

    UFUNCTION(BlueprintCallable)
    virtual void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable)
    virtual void Exit();

    UFUNCTION(BlueprintPure)
    bool IsActive() const { return bActivated; }

    /* 이벤트 메서드 */

    // AbilitySystemComponent::RegisterGameplayTagEvent
    UFUNCTION()
    virtual void OnGameplayEffectTagCountChanged(const FGameplayTag Tag, int32 Count);

protected:
    UFUNCTION(BlueprintNativeEvent)
    void OnEnter();

    UFUNCTION(BlueprintNativeEvent)
    void OnTick(float DeltaTime);

    UFUNCTION(BlueprintNativeEvent)
    void OnExit();

protected:
    UFUNCTION(BlueprintPure)
    FORCEINLINE AActor* GetOwner() const { return Owner.Get(); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UAbilitySystemComponent* GetOwnerAbilitySystem() const { return OwnerAbilitySystem.Get(); }
};
