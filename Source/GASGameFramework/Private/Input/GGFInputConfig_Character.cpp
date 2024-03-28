// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/GGFInputConfig_Character.h"

#include "EnhancedInputComponent.h"
#include "Character/GGFCharacter.h"

void UGGFInputConfig_Character::OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    // GGFCharacter 유효성 검사
    AGGFCharacter* Character = Cast<AGGFCharacter>(EnhancedInputComponent->GetOwner());
    if(Character == nullptr) return;

    /* 캐릭터 움직임 입력 액션 바인딩 */

    // 캐릭터 점프
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, Character, &ACharacter::Jump);
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, Character, &ACharacter::StopJumping);

    // 캐릭터 이동
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, Character, &AGGFCharacter::Move);

    // 카메라 회전
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, Character, &AGGFCharacter::Look);

    // 캐릭터 앉기
    EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, Character, &AGGFCharacter::ToggleCrouch);
}
