// Fill out your copyright notice in the Description page of Project Settings.

#include "GECharacter.h"

#include "EnhancedInputComponent.h"
#include "GEAbilitySystem.h"
#include "Input/GEInputManager.h"

FName AGECharacter::AbilitySystemName(TEXT("AbilitySystem"));
FName AGECharacter::InputManagerName(TEXT("InputManager"));

AGECharacter::AGECharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    /* 서브 오브젝트 생성 */
    AbilitySystem = CreateDefaultSubobject<UGEAbilitySystem>(AbilitySystemName);
    InputManager = CreateDefaultSubobject<UGEInputManager>(InputManagerName);
}

void AGECharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        SetupEnhancedInputComponent(EnhancedInputComponent);
    }
}

void AGECharacter::SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent)
{
    // null 검사
    if(EnhancedInputComponent == nullptr) return;

    // 어빌리티 전용 입력 바인딩
    InputManager->BindEnhancedInput(EnhancedInputComponent);
}
