// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/GGFPawn.h"

#include "GGFGameplayTags.h"
#include "AbilitySystem/GGFDamageableAbilitySystem.h"
#include "Components/GGFGameplayEventManager.h"
#include "Components/GGFGameplayStateMachine.h"

FName AGGFPawn::AbilitySystemName(TEXT("AbilitySystem"));
FName AGGFPawn::GameplayEventManagerName(TEXT("GameplayEventManager"));
FName AGGFPawn::GameplayStateMachineName(TEXT("GameplayStateMachine"));

AGGFPawn::AGGFPawn(const FObjectInitializer& ObjectInitializer)
{
    bReplicates = true;

    /* AbilitySystem */
    AbilitySystem = CreateDefaultSubobject<UGGFDamageableAbilitySystem>(AbilitySystemName);

    /* GameplayEventManager */
    GameplayEventManager = CreateDefaultSubobject<UGGFGameplayEventManager>(GameplayEventManagerName);

    /* GameplayStateMachine */
    GameplayStateMachine = CreateDefaultSubobject<UGGFGameplayStateMachine>(GameplayStateMachineName);
}

void AGGFPawn::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 이벤트 바인딩
    BindEvents();
}

void AGGFPawn::BindEvents()
{
    if(HasAuthority())
    {
        OnServerBindEvents();
    }

    OnBindEvents();
}

void AGGFPawn::OnBindEvents()
{
    // OnDead
    if(auto CastedAbilitySystem = Cast<UGGFDamageableAbilitySystem>(GetAbilitySystem()))
    {
        CastedAbilitySystem->OnDead.AddDynamic(this, &ThisClass::OnDead);
    }
}

void AGGFPawn::OnServerBindEvents()
{
}

void AGGFPawn::OnDead_Implementation()
{
    // TODO Destroy 등 죽음 처리
}
