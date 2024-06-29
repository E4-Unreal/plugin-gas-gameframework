// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFPawnStateMachine.h"

#include "GameplayStates/GGFGS_Dead.h"

UGGFPawnStateMachine::UGGFPawnStateMachine()
{
    StateClasses.Emplace(UGGFGS_Snare::StaticClass());
    StateClasses.Emplace(UGGFGS_Stun::StaticClass());
    StateClasses.Emplace(UGGFGS_Dead::StaticClass());
}
