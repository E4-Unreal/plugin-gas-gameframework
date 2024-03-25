// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GEStateMachine.generated.h"

class UGEStateAbility;

/*
 * 게임플레이 어빌리티를 활용한 캐릭터 전용 상태 머신 컴포넌트입니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GASGAMEFRAMEWORK_API UGEStateMachine : public UActorComponent
{
    GENERATED_BODY()

    // 상태 머신 전용 어빌리티 목록
    UPROPERTY(EditAnywhere, Category = "Config")
    TArray<TSubclassOf<UGEStateAbility>> StateAbilities;

public:
    UGEStateMachine();

    virtual void InitializeComponent() override;
};
