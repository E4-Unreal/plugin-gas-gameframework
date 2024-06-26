// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFActor.h"
#include "GGFDamageableActor.generated.h"

/**
 * 데미지를 입을 수 있는 액터 클래스
 */
UCLASS()
class GGFCORE_API AGGFDamageableActor : public AGGFActor
{
    GENERATED_BODY()

public:
    AGGFDamageableActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void FellOutOfWorld(const UDamageType& dmgType) override;

protected:
    /* GEActor */

    virtual void OnBindEvents() override;

    // 죽음 이벤트
    UFUNCTION(BlueprintNativeEvent)
    void OnDead();
};
