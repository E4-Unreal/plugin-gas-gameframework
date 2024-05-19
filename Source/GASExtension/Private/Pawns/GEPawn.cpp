// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/GEPawn.h"

#include "GEGameplayTags.h"
#include "AbilitySystem/GEDamageableAbilitySystem.h"
#include "Components/GEGameplayEventManager.h"
#include "Components/GEGameplayStateMachine.h"

FName AGEPawn::AbilitySystemName(TEXT("AbilitySystem"));
FName AGEPawn::GameplayEventManagerName(TEXT("GameplayEventManager"));
FName AGEPawn::GameplayStateMachineName(TEXT("GameplayStateMachine"));

AGEPawn::AGEPawn(const FObjectInitializer& ObjectInitializer)
{
    /* AbilitySystem */
    AbilitySystem = CreateDefaultSubobject<UGEDamageableAbilitySystem>(AbilitySystemName);

    /* GameplayEventManager */
    GameplayEventManager = CreateDefaultSubobject<UGEGameplayEventManager>(GameplayEventManagerName);

    /* GameplayStateMachine */
    GameplayStateMachine = CreateDefaultSubobject<UGEGameplayStateMachine>(GameplayStateMachineName);
}

void AGEPawn::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // Dead 태그 이벤트 바인딩
    FOnGameplayEffectTagCountChanged& OnGameplayEffectTagCountChanged =
        GetAbilitySystem()->RegisterGameplayTagEvent(GEGameplayTags::State::Dead, EGameplayTagEventType::NewOrRemoved);
    OnGameplayEffectTagCountChanged.AddUObject(this, &ThisClass::OnDeadTagAdded);
}

void AGEPawn::OnDead_Implementation()
{
    // TODO Destroy 등 죽음 처리
}

void AGEPawn::OnDeadTagAdded(const FGameplayTag Tag, int32 Count)
{
    // 죽음 이벤트 호출
    if(Count > 0) OnDead();
}
