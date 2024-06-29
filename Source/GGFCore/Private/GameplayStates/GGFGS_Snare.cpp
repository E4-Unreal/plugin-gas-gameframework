// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayStates/GGFGS_Snare.h"

#include "GGFGameplayTags.h"
#include "GameFramework/PawnMovementComponent.h"

UGGFGS_Snare::UGGFGS_Snare()
{
    StateTag = State::Debuff::Snare;
}

void UGGFGS_Snare::OnEnter_Implementation()
{
    Super::OnEnter_Implementation();

    if(auto Controller = GetOwnerPawn()->Controller)
    {
        Controller->SetIgnoreMoveInput(true); // 움직임 입력 금지
    }

    GetOwnerPawn()->GetMovementComponent()->StopMovementImmediately(); // 이동 중지
    GetOwnerPawn()->GetMovementComponent()->SetJumpAllowed(false); // 점프 금지
    GetOwnerPawn()->GetMovementComponent()->NavAgentProps.bCanCrouch = false; // 앉기 금지
}

void UGGFGS_Snare::OnExit_Implementation()
{
    GetOwnerPawn()->GetMovementComponent()->NavAgentProps.bCanCrouch = true; // 앉기 허용
    GetOwnerPawn()->GetMovementComponent()->SetJumpAllowed(true); // 점프 허용

    if(auto Controller = GetOwnerPawn()->Controller)
    {
        Controller->SetIgnoreMoveInput(false); // 움직임 입력 허용
    }

    Super::OnExit_Implementation();
}
