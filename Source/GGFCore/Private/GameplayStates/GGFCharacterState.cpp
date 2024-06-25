// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayStates/GGFCharacterState.h"

#include "GameFramework/Character.h"

void UGGFCharacterState::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);

    if(AActor* OwnerActor = GetOwner())
    {
        OwnerCharacter = Cast<ACharacter>(OwnerActor);
        bValid = bValid && OwnerCharacter.IsValid();
    }
}
