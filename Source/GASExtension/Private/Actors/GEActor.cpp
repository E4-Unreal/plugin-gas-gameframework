// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GEActor.h"

#include "AbilitySystem/GGFAbilitySystem.h"
#include "Components/GEGameplayEventManager.h"
#include "Components/GGFGameplayStateMachine.h"

FName AGEActor::AbilitySystemName(TEXT("AbilitySystem"));
FName AGEActor::GameplayEventManagerName(TEXT("GameplayEventManager"));
FName AGEActor::GameplayStateMachineName(TEXT("GameplayStateMachine"));

AGEActor::AGEActor(const FObjectInitializer& ObjectInitializer)
{
    bReplicates = true;

    /* AbilitySystem */
    AbilitySystem = CreateDefaultSubobject<UGGFAbilitySystem>(AbilitySystemName);

    /* GameplayEventManager */
    GameplayEventManager = CreateDefaultSubobject<UGEGameplayEventManager>(GameplayEventManagerName);

    /* GameplayStateMachine */
    GameplayStateMachine = CreateDefaultSubobject<UGGFGameplayStateMachine>(GameplayStateMachineName);
}

void AGEActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 이벤트 바인딩
    BindEvents();
}

void AGEActor::BindEvents()
{
    if(HasAuthority())
    {
        OnServerBindEvents();
    }

    OnBindEvents();
}

void AGEActor::OnBindEvents()
{
}

void AGEActor::OnServerBindEvents()
{
}
