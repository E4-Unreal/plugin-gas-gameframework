// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/States/GECharacterStateMachine.h"

#include "Character/States/GECharacterState_Dead.h"
#include "FunctionLibraries/GEFunctionLibrary.h"

UGECharacterStateMachine::UGECharacterStateMachine()
{
    bWantsInitializeComponent = true;

    // 기본 상태 등록
    CharacterStates.Add(UGECharacterState_Dead::StaticClass());
}

void UGECharacterStateMachine::InitializeComponent()
{
    Super::InitializeComponent();

    // 캐릭터 상태 등록 (어빌리티 부여)
    UGEFunctionLibrary::GiveAbilitiesToTarget(TArray<TSubclassOf<UGameplayAbility>>(CharacterStates), GetOwner());
}

