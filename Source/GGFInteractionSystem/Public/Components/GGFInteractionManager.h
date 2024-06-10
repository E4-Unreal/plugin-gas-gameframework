// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGFInteractionManager.generated.h"

class UGGFInteractableComponent;

/**
 * 상호작용 주체에게 부착하는 상호작용 전용 컴포넌트입니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFINTERACTIONSYSTEM_API UGGFInteractionManager : public UActorComponent
{
    GENERATED_BODY()

protected:
    // 현재 상호작용 가능한 액터
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<AActor> InteractableActor;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UGGFInteractableComponent> InteractableComponent;

public:
    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void Interact();

    UFUNCTION(BlueprintPure)
    virtual bool CanInteract() const;

public:
    /* Setter */

    // 상호작용 가능한 액터 설정
    UFUNCTION(BlueprintCallable)
    virtual void SetInteractableActor(AActor* NewInteractableActor, bool bTraceResult);
};
