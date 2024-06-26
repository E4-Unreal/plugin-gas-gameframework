﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEAbilitySystem.h"
#include "GEDamageableAbilitySystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeadSignature);

/**
 * 체력 어트리뷰트가 기본적으로 등록되어 있으며 체력 어트리뷰트 값이 0이 되면 죽음 관련 이벤트가 호출됩니다.
 */
UCLASS()
class GASEXTENSION_API UGEDamageableAbilitySystem : public UGEAbilitySystem
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnDeadSignature OnDead;

protected:
    // 기본 체력
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Default")
    float MaxHealth = 100;

public:
    UGEDamageableAbilitySystem();

    /* API */
    UFUNCTION(BlueprintPure)
    bool IsDead() const;

protected:

    /* GEAbilitySystem */

    virtual void LocalInitializeComponent_Implementation() override;
    virtual void ServerInitializeComponent_Implementation() override;

    // 체력 어트리뷰트가 0이 되었을 때 호출되는 이벤트 메서드로 서버에서만 호출됩니다.
    UFUNCTION(BlueprintNativeEvent, Category = "ServerOnly")
    void InternalOnDead();

    // 체력 값 변경 이벤트 등록
    virtual void RegisterHealthValueChangeEvent();

    UFUNCTION()
    virtual void OnDeadTagAdded(const FGameplayTag Tag, int32 Count);
};
