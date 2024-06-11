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

public:
    UGGFActorComponent();

    virtual void BeginPlay() override;

protected:
    UFUNCTION(BlueprintPure)
    virtual FORCEINLINE bool IsValid() const { return true; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }
};
