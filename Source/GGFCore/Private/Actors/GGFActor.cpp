// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFActor.h"

#include "AbilitySystem/GGFAbilitySystem.h"
#include "Components/GGFGameplayEventManager.h"
#include "Components/GGFGameplayStateMachine.h"

FName AGGFActor::AbilitySystemName(TEXT("AbilitySystem"));
FName AGGFActor::GameplayEventManagerName(TEXT("GameplayEventManager"));
FName AGGFActor::GameplayStateMachineName(TEXT("GameplayStateMachine"));

AGGFActor::AGGFActor(const FObjectInitializer& ObjectInitializer)
{
    bReplicates = true;

    /* AbilitySystem */
    AbilitySystem = CreateDefaultSubobject<UGGFAbilitySystem>(AbilitySystemName);

    /* GameplayEventManager */
    GameplayEventManager = CreateDefaultSubobject<UGGFGameplayEventManager>(GameplayEventManagerName);

    /* GameplayStateMachine */
    GameplayStateMachine = CreateDefaultSubobject<UGGFGameplayStateMachine>(GameplayStateMachineName);
}

void AGGFActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 이벤트 바인딩
    BindEvents();
}

void AGGFActor::BindEvents()
{
    if(HasAuthority())
    {
        OnServerBindEvents();
    }

    OnBindEvents();
}

void AGGFActor::OnBindEvents()
{
}

void AGGFActor::OnServerBindEvents()
{
}
