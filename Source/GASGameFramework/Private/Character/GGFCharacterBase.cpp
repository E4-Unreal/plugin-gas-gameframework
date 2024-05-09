// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/GGFCharacterBase.h"

#include "Character/Components/GGFCharacterMovement.h"
#include "Abilities/GGFStateMachine.h"
#include "Equipment/Components/GGFEquipmentManager.h"

FName AGGFCharacterBase::EquipmentManagerName(TEXT("EquipmentManager"));
FName AGGFCharacterBase::StateMachineName(TEXT("StateMachine"));

AGGFCharacterBase::AGGFCharacterBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer
    .SetDefaultSubobjectClass<UGGFCharacterMovement>(CharacterMovementComponentName))
{
    /* 서브 오브젝트 생성 */
    EquipmentManager = CreateDefaultSubobject<UGGFEquipmentManager>(EquipmentManagerName);
    StateMachine = CreateDefaultSubobject<UGGFStateMachine>(StateMachineName);
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
