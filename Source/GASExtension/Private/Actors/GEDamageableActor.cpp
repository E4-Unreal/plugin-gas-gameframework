// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GEDamageableActor.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "GEGameplayTags.h"

class UGEDamageableAbilitySystem;

AGEDamageableActor::AGEDamageableActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UGEDamageableAbilitySystem>(AbilitySystemName))
{

}

void AGEDamageableActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // Dead 태그 이벤트 바인딩
    FOnGameplayEffectTagCountChanged& OnGameplayEffectTagCountChanged =
        GetAbilitySystem()->RegisterGameplayTagEvent(GEGameplayTags::State::Dead, EGameplayTagEventType::NewOrRemoved);
    OnGameplayEffectTagCountChanged.AddUObject(this, &ThisClass::OnDeadTagAdded);
}

void AGEDamageableActor::OnDead_Implementation()
{
    // TODO Destroy 등 죽음 처리
}

void AGEDamageableActor::OnDeadTagAdded(const FGameplayTag Tag, int32 Count)
{
    // 죽음 이벤트 호출
    if(Count > 0) OnDead();
}
