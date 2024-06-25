// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayStates/GGFPawnState.h"

void UGGFPawnState::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);

    if(auto OwnerActor = GetOwner())
    {
        OwnerPawn = Cast<APawn>(OwnerActor);
        bValid = bValid && OwnerPawn.IsValid();
    }
}
