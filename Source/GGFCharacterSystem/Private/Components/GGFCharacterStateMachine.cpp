﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFCharacterStateMachine.h"

#include "States/GGFCharacterState_Dead.h"

UGGFCharacterStateMachine::UGGFCharacterStateMachine()
{
    StateClasses.AddUnique(UGGFCharacterState_Dead::StaticClass());
}
