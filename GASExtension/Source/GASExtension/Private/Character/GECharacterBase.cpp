// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GECharacterBase.h"

#include "GEAbilitySystemBase.h"
#include "Character/GEStateMachine.h"
#include "Character/Components/GECharacterMovement.h"

FName AGECharacterBase::AbilitySystemComponentName(TEXT("AbilitySystem"));
FName AGECharacterBase::StateMachineName(TEXT("StateMachine"));

AGECharacterBase::AGECharacterBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer
    .SetDefaultSubobjectClass<UGECharacterMovement>(CharacterMovementComponentName))
{
    /* 서브 오브젝트 생성 */
    AbilitySystem = CreateDefaultSubobject<UGEAbilitySystemBase>(AbilitySystemComponentName);
    StateMachine = CreateDefaultSubobject<UGEStateMachine>(StateMachineName);
}

UAbilitySystemComponent* AGECharacterBase::GetAbilitySystemComponent() const
{
    return AbilitySystem;
}

