// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "GGFGameplayState.generated.h"

class UAbilitySystemComponent;

/**
 * 기본 게임플레이 스테이트 클래스
 */
UCLASS(Blueprintable, BlueprintType, HideDropdown)
class GGFCORE_API UGGFGameplayState : public UObject
{
    GENERATED_BODY()

    /* 레퍼런스 */

    TWeakObjectPtr<AActor> Owner;

    TWeakObjectPtr<UAbilitySystemComponent> OwnerAbilitySystem;

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (Categories = "State"))
    FGameplayTag StateTag;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bValid;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bActivated;

public:
    /* 이벤트 */

    UFUNCTION()
    virtual void OnGameplayEffectTagCountChanged(const FGameplayTag Tag, int32 Count);

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void SetOwner(AActor* NewOwner);

    UFUNCTION(BlueprintPure)
    bool IsValid() const;

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

    UFUNCTION(BlueprintCallable)
    void Enter();

    UFUNCTION(BlueprintCallable)
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable)
    void Exit();

    UFUNCTION(BlueprintPure)
    bool IsActive() const { return bActivated; }

protected:
    /* 메서드 */

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
