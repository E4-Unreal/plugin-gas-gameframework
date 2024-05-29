// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GEAbilitySystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayEventInvoked, const FGameplayTag&, EventTag);

class UGEStatsBase;

/**
 * 가장 기본이 되는 AbilitySystemComponent 클래스입니다.
 *
 * - 기본 적용할 AttributeSet, GameplayEffect, GameplayAbility 목록을 설정할 수 있습니다.
 * - HandleGameplayEvent를 확장하여 EventTag 멀티캐스트 기능을 추가하였습니다.
 */
UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class GASEXTENSION_API UGEAbilitySystem : public UAbilitySystemComponent
{
    GENERATED_BODY()

public:
    // 멀티캐스트 GameplayEvent 사용 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Replication")
    bool bUseMulticastGameplayEvent = false;

    // GameplayEvent 멀티캐스트에서 호출되는 델리게이트
    UPROPERTY(BlueprintAssignable)
    FOnGameplayEventInvoked OnGameplayEventInvoked;

protected:
    // 기본으로 사용할 AttributeSet 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Default")
    TArray<TSubclassOf<UAttributeSet>> Attributes;

    // 기본으로 사용할 Stats 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Default")
    TArray<TSubclassOf<UGEStatsBase>> Stats;

    // 기본으로 적용시킬 GameplayEffect 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Default")
    TArray<TSubclassOf<UGameplayEffect>> Effects;

    // 기본으로 부여할 GameplayAbility 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Default")
    TArray<TSubclassOf<UGameplayAbility>> Abilities;

    // 기본으로 부여할 GameplayTag 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Default")
    FGameplayTagContainer GameplayTags;

public:
    UGEAbilitySystem();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* AbilitySystemComponent */

    // 게임플레이 태그 이벤트 멀티캐스트 기능을 추가하였습니다. EventTag만 멀티캐스트됩니다.
    virtual int32 HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload) override;

protected:
    /* 메서드 */

    // 서버 전용 초기화 메서드
    UFUNCTION(BlueprintNativeEvent)
    void ServerInitializeComponent();

    // 서버, 클라이언트 공통 초기화 메서드
    UFUNCTION(BlueprintNativeEvent)
    void LocalInitializeComponent();

    // 게임플레이 태그 이벤트를 멀티캐스트합니다.
    UFUNCTION(NetMulticast, Unreliable, Category = "GameplayEvent")
    virtual void NetMulticast_HandleGameplayEvent(FGameplayTag EventTag);
};
