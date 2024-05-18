// Fill out your copyright notice in the Description page of Project Settings.

#include "Animations/GECharacterAnimInstance.h"

#include "GameFramework/Character.h"

void UGECharacterAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    // 레퍼런스 할당
    OwningCharacter = Cast<ACharacter>(GetOwningActor());
    if(OwningCharacter)
    {
        OwningCharacterMovement = OwningCharacter->GetCharacterMovement();
    }
}
