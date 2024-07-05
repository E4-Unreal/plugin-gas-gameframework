// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGFGameplayStateMachine.generated.h"

class UGGFGameplayState;

/**
 * ASC에 부착되는 게임 플레이 태그를 하나의 상태로서 취급하여 동작하는 상태 머신 클래스
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFCORE_API UGGFGameplayStateMachine : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    bool bValid;

    // 사용할 모든 상태 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UGGFGameplayState>> StateClasses;

    // 생성된 모든 상태 인스턴스 목록
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<UGGFGameplayState>> StateInstances;

public:
    UGGFGameplayStateMachine();

    /* ActorComponent */

    virtual void InitializeComponent() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    virtual void CreateGameplayStateInstances();
};
