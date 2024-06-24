// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGFActorComponent.generated.h"

/**
 * GASGameFramework 플러그인에서 자주 사용하는 설정이 적용된 기본 액터 컴포넌트 클래스입니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFCORE_API UGGFActorComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    bool bValid = true;

public:
    UGGFActorComponent();

    virtual void BeginPlay() override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void Reset() { }

protected:
    UFUNCTION(BlueprintPure)
    virtual FORCEINLINE bool IsValid() const { return bValid; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }
};
