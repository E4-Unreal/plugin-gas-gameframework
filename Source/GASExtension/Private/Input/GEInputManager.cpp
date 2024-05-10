﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/GEInputManager.h"

#include "EnhancedInputSubsystems.h"
#include "Input/GEInputConfig.h"

void UGEInputManager::BeginPlay()
{
    Super::BeginPlay();

    // 입력 매핑 컨텍스트 등록
    RegisterInputMappingContexts();
}

void UGEInputManager::BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    // EnhancedInputComponent null 검사
    if(EnhancedInputComponent == nullptr) return;

    for (TObjectPtr<UGEInputConfig> InputConfig : InputConfigs)
    {
        // 유효성 검사
        if(!InputConfig) continue;

        // 향상된 입력 바인딩
        InputConfig->BindEnhancedInput(EnhancedInputComponent);
    }
}

void UGEInputManager::RegisterInputMappingContexts()
{
    // Pawn 유효성 검사
    const APawn* Pawn = Cast<APawn>(GetOwner());
    if(Pawn == nullptr) return;

    // PlayerController 유효성 검사
    const APlayerController* PlayerController = Cast<APlayerController>(Pawn->Controller);
    if(PlayerController == nullptr) return;

    // 기본 입력 매핑 컨텍스트 추가
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
        for (const auto& MappingContext : InputMappingContexts)
        {
            Subsystem->AddMappingContext(MappingContext, 0);
        }
    }
}