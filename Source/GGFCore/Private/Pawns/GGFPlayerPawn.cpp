// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/GGFPlayerPawn.h"

#include "EnhancedInputComponent.h"
#include "Input/GEInputManager.h"

class UGGFPlayerAbilitySystem;

FName AGGFPlayerPawn::InputManagerName(TEXT("InputManager"));

AGGFPlayerPawn::AGGFPlayerPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UGGFPlayerAbilitySystem>(AbilitySystemName))
{
    /* InputManager */
    InputManager = CreateDefaultSubobject<UGEInputManager>(InputManagerName);
}

void AGGFPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        SetupEnhancedInputComponent(EnhancedInputComponent);
    }
}

void AGGFPlayerPawn::SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent)
{
    // null 검사
    if(EnhancedInputComponent == nullptr) return;

    // 어빌리티 전용 입력 바인딩
    InputManager->BindEnhancedInput(EnhancedInputComponent);
}
