// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/GGFInputConfig.h"

#include "EnhancedInputComponent.h"

void UGGFInputConfig::BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    // EnhancedInputComponent null 검사
    if(EnhancedInputComponent == nullptr || EnhancedInputComponent->GetOwner() == nullptr) return;

    // 바인딩
    OnBindEnhancedInput(EnhancedInputComponent);
}
