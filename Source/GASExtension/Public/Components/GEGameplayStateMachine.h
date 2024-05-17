// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "GEGameplayStateMachine.generated.h"

class UAbilitySystemComponent;
/**
 * GameplayStateMachine에서 사용되는 상태 클래스
 */
UCLASS(Blueprintable, BlueprintType, HideDropdown)
class GASEXTENSION_API UGEGameplayState : public UObject
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
    FORCEINLINE bool IsValid() const;

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

    virtual void Enter();

    virtual void Exit();

    UFUNCTION()
    virtual void OnGameplayEffectTagCountChanged(const FGameplayTag Tag, int32 Count);

protected:
    UFUNCTION(BlueprintNativeEvent)
    void OnEnter();

    UFUNCTION(BlueprintNativeEvent)
    void OnExit();

protected:
    UFUNCTION(BlueprintPure)
    FORCEINLINE AActor* GetOwner() const { return Owner.Get(); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UAbilitySystemComponent* GetOwnerAbilitySystem() const { return OwnerAbilitySystem.Get(); }
};

/**
 * 캐릭터 전용 GameplayEventAction 클래스입니다.
 */
UCLASS(HideDropdown)
class GASEXTENSION_API UGECharacterState : public UGEGameplayState
{
    GENERATED_BODY()

    TWeakObjectPtr<ACharacter> OwnerCharacter;

public:
    virtual void SetOwner(AActor* NewOwner) override;

protected:
    UFUNCTION(BlueprintPure)
    FORCEINLINE ACharacter* GetOwnerCharacter() const { return OwnerCharacter.Get(); }
};

/**
 * ASC에 부착되는 게임 플레이 태그를 하나의 상태로서 취급하여 동작하는 상태 머신 액터 컴포넌트입니다.
 * Owner의 AbilitySystemComponent에 의존성을 가지고 있습니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GASEXTENSION_API UGEGameplayStateMachine : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bValid;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UGEGameplayState>> GameplayStates;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    TArray<TObjectPtr<UGEGameplayState>> GameplayStateInstances;

public:
    UGEGameplayStateMachine();

    virtual void InitializeComponent() override;

protected:
    virtual void CreateGameplayStateInstances();
};
