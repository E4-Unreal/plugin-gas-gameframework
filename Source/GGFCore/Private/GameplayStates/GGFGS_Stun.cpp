// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayStates/GGFGS_Stun.h"

#include "GGFGameplayTags.h"

UGGFGS_Stun::UGGFGS_Stun()
{
    StateTag = State::Stun;
}

void UGGFGS_Stun::OnEnter_Implementation()
{
    Super::OnEnter_Implementation();

    if(auto Controller = GetOwnerPawn()->Controller)
    {
        Controller->SetIgnoreLookInput(true); // 회전 입력 금지
    }
}

void UGGFGS_Stun::OnExit_Implementation()
{
    if(auto Controller = GetOwnerPawn()->Controller)
    {
        Controller->SetIgnoreLookInput(false); // 회전 입력 허용
    }

    Super::OnExit_Implementation();
}
