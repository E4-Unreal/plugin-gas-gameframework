// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GEPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "Input/GEInputManager.h"

class UGEPlayerAbilitySystem;

FName AGEPlayerCharacter::InputManagerName(TEXT("InputManager"));

AGEPlayerCharacter::AGEPlayerCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UGEPlayerAbilitySystem>(AbilitySystemName))
{
    /* InputManager */
    InputManager = CreateDefaultSubobject<UGEInputManager>(InputManagerName);
}

void AGEPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        SetupEnhancedInputComponent(EnhancedInputComponent);
    }
}

void AGEPlayerCharacter::SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent)
{
    // null 검사
    if(EnhancedInputComponent == nullptr) return;

    // 어빌리티 전용 입력 바인딩
    InputManager->BindEnhancedInput(EnhancedInputComponent);
}
