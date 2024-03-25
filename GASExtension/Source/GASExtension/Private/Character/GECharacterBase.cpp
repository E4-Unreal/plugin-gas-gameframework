// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GECharacterBase.h"

#include "EnhancedInputComponent.h"
#include "GEAbilitySystemBase.h"
#include "Character/Components/GEAbilityInputBinder.h"
#include "Character/Components/GECharacterMovement.h"
#include "Abilities/GEStateMachine.h"
#include "Equipment/Components/GEEquipmentManager.h"

FName AGECharacterBase::AbilitySystemComponentName(TEXT("AbilitySystem"));
FName AGECharacterBase::EquipmentManagerName(TEXT("EquipmentManager"));
FName AGECharacterBase::StateMachineName(TEXT("StateMachine"));

AGECharacterBase::AGECharacterBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer
    .SetDefaultSubobjectClass<UGECharacterMovement>(CharacterMovementComponentName))
{
    /* 서브 오브젝트 생성 */
    AbilitySystem = CreateDefaultSubobject<UGEAbilitySystemBase>(AbilitySystemComponentName);
    AbilityInputBinder = CreateDefaultSubobject<UGEAbilityInputBinder>(TEXT("AbilityInputBinder"));
    EquipmentManager = CreateDefaultSubobject<UGEEquipmentManager>(EquipmentManagerName);
    StateMachine = CreateDefaultSubobject<UGEStateMachine>(StateMachineName);
}

void AGECharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        SetupEnhancedInputComponent(EnhancedInputComponent);
    }
}

void AGECharacterBase::SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent)
{
    // null 검사
    if(EnhancedInputComponent == nullptr) return;

    // 어빌리티 전용 입력 바인딩
    AbilityInputBinder->BindAbilityInput(EnhancedInputComponent);
}

bool AGECharacterBase::CanJumpInternal_Implementation() const
{
    // 앉은 상태에서도 점프가 가능합니다.
    return JumpIsAllowedInternal();
}

bool AGECharacterBase::CanCrouch() const
{
    // 점프 상태에서는 앉기가 불가능합니다.
    return !GetCharacterMovement()->IsFalling() && Super::CanCrouch();
}
