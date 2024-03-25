// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GEStateMachine.h"

#include "Character/States/GECSA_Dead.h"
#include "FunctionLibraries/GEFunctionLibrary.h"

UGEStateMachine::UGEStateMachine()
{
    bWantsInitializeComponent = true;
}

void UGEStateMachine::InitializeComponent()
{
    Super::InitializeComponent();

    // 캐릭터 상태 등록 (어빌리티 부여)
    UGEFunctionLibrary::GiveAbilitiesToTarget(TArray<TSubclassOf<UGameplayAbility>>(StateAbilities), GetOwner());
}

