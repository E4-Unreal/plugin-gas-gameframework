// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFTriggerBox.h"
#include "GGFEffectArea.generated.h"

class UGGFEffectAreaComponent;

/**
 * 주기적으로 오버랩된 액터들에게 게임플레이 이펙트를 적용하는 트리거 박스 액터입니다.
 */
UCLASS()
class GGFCORE_API AGGFEffectArea : public AGGFTriggerBox
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetEffectAreaComponent, Category = "Component")
    TObjectPtr<UGGFEffectAreaComponent> EffectAreaComponent;

public:
    AGGFEffectArea(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void PostInitializeComponents() override;
    virtual void BeginPlay() override;

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFEffectAreaComponent* GetEffectAreaComponent() const { return EffectAreaComponent; }
};
