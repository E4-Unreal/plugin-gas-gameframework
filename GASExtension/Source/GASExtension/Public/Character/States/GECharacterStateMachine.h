// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GECharacterStateMachine.generated.h"

class UGECharacterState;

// TODO 나중에 폰 전용 상태 머신 컴포넌트로 추상화할 수도 있습니다.
/*
 * 게임플레이 어빌리티를 활용한 캐릭터 전용 상태 머신 컴포넌트입니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GASEXTENSION_API UGECharacterStateMachine : public UActorComponent
{
    GENERATED_BODY()

    // 캐릭터 상태 머신 전용 어빌리티 목록
    UPROPERTY(EditAnywhere, Category = "Config")
    TArray<TSubclassOf<UGECharacterState>> CharacterStates;

public:
    UGECharacterStateMachine();

    virtual void InitializeComponent() override;
};
