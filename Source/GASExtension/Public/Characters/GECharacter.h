// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GECharacter.generated.h"

class UGEGameplayEventManager;
class UGEGameplayStateMachine;

/**
 * GAS를 사용하기 위한 기본 캐릭터 클래스
 *
 * DamageableAbilitySystem이 기본으로 탑재되어 있습니다.
 */
UCLASS()
class GASEXTENSION_API AGECharacter : public ACharacter, public IAbilitySystemInterface
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

protected:
    // 캐릭터 메시에서 기본적으로 숨길 스켈레톤 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|CharacterMesh")
    TArray<FName> BoneNamesToHide;

public:
    AGECharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void PostInitializeComponents() override;

protected:
    // 죽음 이벤트
    UFUNCTION(BlueprintNativeEvent)
    void OnDead();

    UFUNCTION()
    virtual void OnDeadTagAdded(const FGameplayTag Tag, int32 Count);

    // BoneNamesToHide에 설정된 스켈레톤을 숨깁니다.
    UFUNCTION(BlueprintCallable)
    virtual void HideBones();

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
