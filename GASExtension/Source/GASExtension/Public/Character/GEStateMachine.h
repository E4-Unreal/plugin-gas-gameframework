// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GEStateMachine.generated.h"


struct FGameplayTagContainer;
struct FGameplayTag;
class UGEState;
class UAbilitySystemComponent;
/**
 * 게임플레이 태그 기반의 상태 머신으로 캐릭터 클래스에서 사용합니다.
 * 상태 전이 조건은 GAS에서 처리할 것으로 기대되기 때문에 따로 구현하지 않았습니다.
 */
UCLASS(ClassGroup=(GASExtension), meta=(BlueprintSpawnableComponent))
class GASEXTENSION_API UGEStateMachine : public UActorComponent
{
    GENERATED_BODY()

    TWeakObjectPtr<UAbilitySystemComponent> AbilitySystem;

protected:

    // 설정을 위한 프로퍼티로 실제 코드에서는 StatesMap을 사용합니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<TSubclassOf<UGEState>> StateClasses;

    // StatesToUse 프로퍼티 중 유효한 상태만 선택하여 생성된 상태 맵입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true), Transient)
    TArray<TObjectPtr<UGEState>> States;

    // 현재 활성화된 상태 목록입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true), Transient)
    TArray<TObjectPtr<UGEState>> ActivatedStates;

public:
    UGEStateMachine();

    virtual void InitializeComponent() override;

protected:
    UFUNCTION()
    virtual void OnGameplayEffectTagCountChanged_Event(const FGameplayTag Tag, int32 NewCount);

private:
    void RegisterGameplayTagEvent();
    void CreateStates();

public:
    /* Getter */
    UFUNCTION(BlueprintPure)
    FORCEINLINE UAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem.Get(); }
};
