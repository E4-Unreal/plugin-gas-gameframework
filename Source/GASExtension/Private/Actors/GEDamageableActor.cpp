// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GEDamageableActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/GGFDamageableAbilitySystem.h"

AGEDamageableActor::AGEDamageableActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UGGFDamageableAbilitySystem>(AbilitySystemName))
{

}

void AGEDamageableActor::OnBindEvents()
{
    Super::OnBindEvents();

    // OnDead
    if(auto CastedAbilitySystem = Cast<UGGFDamageableAbilitySystem>(GetAbilitySystem()))
    {
        CastedAbilitySystem->OnDead.AddDynamic(this, &ThisClass::OnDead);
    }
}

void AGEDamageableActor::OnDead_Implementation()
{

}
