// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GECharacterState.h"

#include "AbilitySystemComponent.h"
#include "Character/GEStateMachine.h"
#include "GameFramework/Character.h"

void UGECharacterState::OnInit_Implementation()
{
    Super::OnInit_Implementation();

    Character = Cast<ACharacter>(GetStateMachine()->GetAbilitySystem()->GetOwnerActor());
}
