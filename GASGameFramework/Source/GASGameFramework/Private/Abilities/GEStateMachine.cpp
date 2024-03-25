// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFStateMachine.h"

#include "Character/States/GGFCSA_Dead.h"
#include "FunctionLibraries/GGFFunctionLibrary.h"

UGGFStateMachine::UGGFStateMachine()
{
    bWantsInitializeComponent = true;
}

void UGGFStateMachine::InitializeComponent()
{
    Super::InitializeComponent();

    // 캐릭터 상태 등록 (어빌리티 부여)
    UGGFFunctionLibrary::GiveAbilitiesToTarget(TArray<TSubclassOf<UGameplayAbility>>(StateAbilities), GetOwner());
}

