// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/GGFInputConfig_Character.h"

#include "EnhancedInputComponent.h"
#include "Characters/GGFPlayerCharacter.h"

void UGGFInputConfig_Character::OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    // GGFCharacter 유효성 검사
    AGGFPlayerCharacter* Character = Cast<AGGFPlayerCharacter>(EnhancedInputComponent->GetOwner());
    if(Character == nullptr) return;

    /* 캐릭터 움직임 입력 액션 바인딩 */

    // 캐릭터 점프
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, Character, &ACharacter::Jump);
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, Character, &ACharacter::StopJumping);

    // 캐릭터 이동
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, Character, &AGGFPlayerCharacter::Move);

    // 카메라 회전
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, Character, &AGGFPlayerCharacter::Look);

    // 캐릭터 앉기
    EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, Character, &AGGFPlayerCharacter::ToggleCrouch);
}
