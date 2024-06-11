// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFActorComponent.h"
#include "GGFCoreLogging.h"

UGGFActorComponent::UGGFActorComponent()
{
    bWantsInitializeComponent = true;
}

void UGGFActorComponent::BeginPlay()
{
    Super::BeginPlay();

#if WITH_EDITOR
    if(IsNotValid())
    {
        LOG_ACTOR_COMPONENT_DETAIL(Error, TEXT("IsNotValid"))
    }
#endif
}
