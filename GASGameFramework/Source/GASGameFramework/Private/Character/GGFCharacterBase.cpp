// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GGFCharacterBase.h"

#include "EnhancedInputComponent.h"
#include "GGFAbilitySystemBase.h"
#include "Character/Components/GGFAbilityInputBinder.h"
#include "Character/Components/GGFCharacterMovement.h"
#include "Abilities/GGFStateMachine.h"
#include "Equipment/Components/GGFEquipmentManager.h"

FName AGGFCharacterBase::AbilitySystemComponentName(TEXT("AbilitySystem"));
FName AGGFCharacterBase::EquipmentManagerName(TEXT("EquipmentManager"));
FName AGGFCharacterBase::StateMachineName(TEXT("StateMachine"));

AGGFCharacterBase::AGGFCharacterBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer
    .SetDefaultSubobjectClass<UGGFCharacterMovement>(CharacterMovementComponentName))
{
    /* 서브 오브젝트 생성 */
    AbilitySystem = CreateDefaultSubobject<UGGFAbilitySystemBase>(AbilitySystemComponentName);
    AbilityInputBinder = CreateDefaultSubobject<UGGFAbilityInputBinder>(TEXT("AbilityInputBinder"));
    EquipmentManager = CreateDefaultSubobject<UGGFEquipmentManager>(EquipmentManagerName);
    StateMachine = CreateDefaultSubobject<UGGFStateMachine>(StateMachineName);
}

void AGGFCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        SetupEnhancedInputComponent(EnhancedInputComponent);
    }
}

void AGGFCharacterBase::SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent)
{
    // null 검사
    if(EnhancedInputComponent == nullptr) return;

    // 어빌리티 전용 입력 바인딩
    AbilityInputBinder->BindAbilityInput(EnhancedInputComponent);
}

bool AGGFCharacterBase::CanJumpInternal_Implementation() const
{
    // 앉은 상태에서도 점프가 가능합니다.
    return JumpIsAllowedInternal();
}

bool AGGFCharacterBase::CanCrouch() const
{
    // 점프 상태에서는 앉기가 불가능합니다.
    return !GetCharacterMovement()->IsFalling() && Super::CanCrouch();
}
