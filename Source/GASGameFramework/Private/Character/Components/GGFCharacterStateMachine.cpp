// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Components/GGFCharacterStateMachine.h"

#include "Character/States/GGFCharacterState_Dead.h"

UGGFCharacterStateMachine::UGGFCharacterStateMachine()
{
    StateClasses.AddUnique(UGGFCharacterState_Dead::StaticClass());
}
