// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GGFActorComponent.h"
#include "GGFTriggerComponent.generated.h"

/**
 * 연동된 액터들을 활성화 혹은 비활성화하는 액터 컴포넌트입니다.
 * 주로 버튼 같은 기믹에서 사용됩니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFGIMMICKSYSTEM_API UGGFTriggerComponent : public UGGFActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference", meta = (MustImplement = "GGFActivationInterface"))
    TArray<TObjectPtr<AActor>> Targets;

    // 비활성화된 상태에서만 활성화가 가능해지는 옵션입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bShouldToggle = true;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    bool bActivated = false;

public:
    /* API */

    UFUNCTION(BlueprintCallable, Category = "TriggerComponent")
    virtual void ToggleActivateTargets();

    UFUNCTION(BlueprintCallable, Category = "TriggerComponent")
    virtual void ActivateTargets();

    UFUNCTION(BlueprintCallable, Category = "TriggerComponent")
    virtual void DeactivateTargets();

    UFUNCTION(BlueprintPure, Category = "TriggerComponent")
    FORCEINLINE bool IsActivated() const { return bActivated; }

protected:
    /* GGFActorComponent */

    virtual FORCEINLINE bool IsValid() const override { return !Targets.IsEmpty(); }
};
