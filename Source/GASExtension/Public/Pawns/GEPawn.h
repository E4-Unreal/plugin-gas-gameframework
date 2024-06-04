// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Pawn.h"
#include "GEPawn.generated.h"

class UGEGameplayEventManager;
class UGEGameplayStateMachine;

/**
 * GAS를 사용하기 위한 기본 폰 클래스
 *
 * DamageableAbilitySystem이 기본으로 탑재되어 있습니다.
 */
UCLASS()
class GASEXTENSION_API AGEPawn : public APawn, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    // AbilitySystem 서브 오브젝트 이름
    static FName AbilitySystemName;

    // GameplayEventManager 서브 오브젝트 이름
    static FName GameplayEventManagerName;

    // GameplayStateMachine 서브 오브젝트 이름
    static FName GameplayStateMachineName;

private:
    /* 컴포넌트 */

    // GAS를 사용하기 위한 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetAbilitySystem, Category = "Component")
    TObjectPtr<UAbilitySystemComponent> AbilitySystem;

    // 멀티캐스트 게임플레이 태그 이벤트를 사용하기 위한 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetGameplayEventManager, Category = "Component")
    TObjectPtr<UGEGameplayEventManager> GameplayEventManager;

    // 게임 플레이 태그 상태 머신 액터 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetGameplayStateMachine, Category = "Component")
    TObjectPtr<UGEGameplayStateMachine> GameplayStateMachine;

public:
    AGEPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void PostInitializeComponents() override;

protected:
    /* 메서드 */

    // 이벤트 바인딩 전용 메서드로 PostInitializeComponents에서 호출됩니다.
    void BindEvents();

    // 서버, 클라이언트 모두 필요한 이벤트 바인딩
    virtual void OnBindEvents();

    // 서버에서만 필요한 이벤트 바인딩
    virtual void OnServerBindEvents();

    // 죽음 이벤트
    UFUNCTION(BlueprintNativeEvent)
    void OnDead();

protected:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGEGameplayEventManager* GetGameplayEventManager() const { return GameplayEventManager; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGEGameplayStateMachine* GetGameplayStateMachine() const { return GameplayStateMachine; }

public:
    /* AbilitySystemInterface */

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; }
};
