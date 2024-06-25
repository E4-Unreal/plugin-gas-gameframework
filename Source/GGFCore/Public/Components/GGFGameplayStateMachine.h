// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "GGFGameplayStateMachine.generated.h"

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

/**
 * 캐릭터 전용 GameplayEventAction 클래스입니다.
 */
UCLASS(HideDropdown)
class GGFCORE_API UGGFCharacterState : public UGGFGameplayState
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
class GGFCORE_API UGGFGameplayStateMachine : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    bool bValid;

    // 사용할 모든 상태 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UGGFGameplayState>> StateClasses;

    // 생성된 모든 상태 인스턴스 목록
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<UGGFGameplayState>> StateInstances;

public:
    UGGFGameplayStateMachine();

    /* ActorComponent */

    virtual void InitializeComponent() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    virtual void CreateGameplayStateInstances();
};
