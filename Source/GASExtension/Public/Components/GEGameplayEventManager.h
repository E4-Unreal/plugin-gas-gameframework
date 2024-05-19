// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "GEGameplayEventManager.generated.h"

/**
 * GameplayEvent에 대응하는 동작을 수행하기 위한 클래스로
 * 기능 로직 구현을 Actor에서 분리하기 위해 제작되었습니다.
 *
 * GameplayAbility와 다른 점은 멀티캐스트 전용이라는 것입니다.
 */
UCLASS(Blueprintable, BlueprintType, HideDropdown)
class GASEXTENSION_API UGEGameplayEventAction : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (Categories = "Event"))
    FGameplayTag EventTag;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bValid;

private:
    TWeakObjectPtr<AActor> Owner;

public:
    UFUNCTION(BlueprintCallable)
    virtual void SetOwner(AActor* NewOwner);

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsValid() const;

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void ActivateAction();

protected:
    UFUNCTION(BlueprintPure)
    FORCEINLINE AActor* GetOwner() const { return Owner.Get(); }
};

/**
 * 캐릭터 전용 GameplayEventAction 클래스입니다.
 */
UCLASS(HideDropdown)
class GASEXTENSION_API UGECharacterEventAction : public UGEGameplayEventAction
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
 * 멀티캐스트된 게임플레이 태그 이벤트를 관리하는 액터 컴포넌트입니다.
 *
 * Owner의 AbilitySystemComponent는 GEAbilitySystem을 상속받고 있어야 합니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GASEXTENSION_API UGEGameplayEventManager : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bValid;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UGEGameplayEventAction>> GameplayEventActions;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    TArray<TObjectPtr<UGEGameplayEventAction>> GameplayEventActionInstances;

public:
    UGEGameplayEventManager();

    virtual void InitializeComponent() override;

protected:
    virtual void CreateGameplayEventActionInstances();

    UFUNCTION()
    virtual void HandleGameplayEvent(const FGameplayTag& EventTag);
};
