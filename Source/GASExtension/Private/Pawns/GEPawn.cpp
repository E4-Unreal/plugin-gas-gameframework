// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/GEPawn.h"

#include "GGFGameplayTags.h"
#include "AbilitySystem/GGFDamageableAbilitySystem.h"
#include "Components/GEGameplayEventManager.h"
#include "Components/GGFGameplayStateMachine.h"

FName AGEPawn::AbilitySystemName(TEXT("AbilitySystem"));
FName AGEPawn::GameplayEventManagerName(TEXT("GameplayEventManager"));
FName AGEPawn::GameplayStateMachineName(TEXT("GameplayStateMachine"));

AGEPawn::AGEPawn(const FObjectInitializer& ObjectInitializer)
{
    bReplicates = true;

    /* AbilitySystem */
    AbilitySystem = CreateDefaultSubobject<UGGFDamageableAbilitySystem>(AbilitySystemName);

    /* GameplayEventManager */
    GameplayEventManager = CreateDefaultSubobject<UGEGameplayEventManager>(GameplayEventManagerName);

    /* GameplayStateMachine */
    GameplayStateMachine = CreateDefaultSubobject<UGGFGameplayStateMachine>(GameplayStateMachineName);
}

void AGEPawn::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 이벤트 바인딩
    BindEvents();
}

void AGEPawn::BindEvents()
{
    if(HasAuthority())
    {
        OnServerBindEvents();
    }

    OnBindEvents();
}

void AGEPawn::OnBindEvents()
{
    // OnDead
    if(auto CastedAbilitySystem = Cast<UGGFDamageableAbilitySystem>(GetAbilitySystem()))
    {
        CastedAbilitySystem->OnDead.AddDynamic(this, &ThisClass::OnDead);
    }
}

void AGEPawn::OnServerBindEvents()
{
}

void AGEPawn::OnDead_Implementation()
{
    // TODO Destroy 등 죽음 처리
}
