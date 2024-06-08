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

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference")
    TArray<TObjectPtr<AActor>> Targets;

public:
    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void ActivateTargets();

    UFUNCTION(BlueprintCallable)
    virtual void DeactivateTargets();

protected:
    /* GGFActorComponent */

    virtual FORCEINLINE bool IsValid() const override { return !Targets.IsEmpty(); }
};
