﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEActor.h"
#include "GEDamageableActor.generated.h"

/**
 * 데미지를 입을 수 있는 액터 클래스
 */
UCLASS()
class GASEXTENSION_API AGEDamageableActor : public AGEActor
{
    GENERATED_BODY()

public:
    AGEDamageableActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void PostInitializeComponents() override;

protected:
    // 죽음 이벤트
    UFUNCTION(BlueprintNativeEvent)
    void OnDead();

    UFUNCTION()
    virtual void OnDeadTagAdded(const FGameplayTag Tag, int32 Count);
};
