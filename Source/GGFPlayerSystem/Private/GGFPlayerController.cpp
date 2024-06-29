// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/GGFGameModeInterface.h"
#include "InputMappingContext.h"

AGGFPlayerController::AGGFPlayerController()
{
    /* 기본 에셋 설정 */
    ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(TEXT("/GASGameFramework/Input/Player/IMC_Player"));
    if(MappingContextFinder.Succeeded()) MappingContext = MappingContextFinder.Object;

    ConstructorHelpers::FObjectFinder<UInputAction> SpectatePreviousActionFinder(TEXT("/GASGameFramework/Input/Player/IA_SpectatePrevious"));
    if(SpectatePreviousActionFinder.Succeeded()) SpectatePreviousAction = SpectatePreviousActionFinder.Object;

    ConstructorHelpers::FObjectFinder<UInputAction> SpectateNextActionFinder(TEXT("/GASGameFramework/Input/Player/IA_SpectateNext"));
    if(SpectateNextActionFinder.Succeeded()) SpectateNextAction = SpectateNextActionFinder.Object;
}

void AGGFPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // 기본 입력 매핑 컨텍스트 추가
    if (auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(MappingContext, 0);
    }

    if(auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(SpectatePreviousAction, ETriggerEvent::Triggered, this, &ThisClass::OnSpectatePreviousActionTriggered);
        EnhancedInputComponent->BindAction(SpectateNextAction, ETriggerEvent::Triggered, this, &AGGFPlayerController::OnSpectateNextActionTriggered);
    }
}

uint8 AGGFPlayerController::GetTeamID_Implementation() const
{
    if(PlayerState->Implements<UGGFTeamInterface>())
    {
        return Execute_GetTeamID(PlayerState);
    }

    return NoTeam;
}

void AGGFPlayerController::SetTeamID_Implementation(uint8 NewTeamID)
{
    if(PlayerState->Implements<UGGFTeamInterface>())
    {
        return Execute_SetTeamID(PlayerState, NewTeamID);
    }
}

void AGGFPlayerController::OnSpectatePreviousActionTriggered_Implementation()
{
    ServerSpectatePrevious();
}

void AGGFPlayerController::OnSpectateNextActionTriggered_Implementation()
{
    ServerSpectateNext();
}

void AGGFPlayerController::ServerSpectatePrevious_Implementation()
{
    if(auto GameMode = GetWorld()->GetAuthGameMode())
    {
        if(GameMode->Implements<UGGFGameModeInterface>())
        {
            IGGFGameModeInterface::Execute_SetViewTargetToPreviousPlayer(GameMode, this);
        }
    }
}

void AGGFPlayerController::ServerSpectateNext_Implementation()
{
    if(auto GameMode = GetWorld()->GetAuthGameMode())
    {
        if(GameMode->Implements<UGGFGameModeInterface>())
        {
            IGGFGameModeInterface::Execute_SetViewTargetToNextPlayer(GameMode, this);
        }
    }
}
