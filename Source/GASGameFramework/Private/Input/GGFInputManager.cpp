// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/GGFInputManager.h"

#include "Input/GGFInputConfig.h"

void UGGFInputManager::BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    // EnhancedInputComponent null 검사
    if(EnhancedInputComponent == nullptr) return;

    for (TObjectPtr<UGGFInputConfig> InputConfig : InputConfigs)
    {
        // 유효성 검사
        if(!InputConfig) continue;

        // 향상된 입력 바인딩
        InputConfig->BindEnhancedInput(EnhancedInputComponent);
    }
}
