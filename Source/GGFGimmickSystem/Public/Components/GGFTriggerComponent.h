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
    // 트리거 동작 시 활성화할 대상 액터 그룹
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference", meta = (MustImplement = "GGFActivatableInterface"))
    TArray<TObjectPtr<AActor>> TargetsToActivate;

    // true 설정된 경우 트리거를 여러 번 동작시킬 수 있습니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bCanRetrigger = true;

protected:
    // 트리거 동작 여부
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    bool bTriggered = false;

public:
    /* API */

    // 대상 액터 그룹 활성화 혹은 비활성화
    UFUNCTION(BlueprintCallable)
    virtual void ToggleTargets();

    // 대상 액터 그룹 활성화
    UFUNCTION(BlueprintCallable)
    virtual void ActivateTargets();

    // 대상 액터 그룹 비활성화
    UFUNCTION(BlueprintCallable)
    virtual void DeactivateTargets();

    // 트리거 동작 여부
    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsTriggered() const { return bTriggered; }

protected:
    /* GGFActorComponent */

    virtual FORCEINLINE bool IsValid() const override { return !TargetsToActivate.IsEmpty(); }
};
