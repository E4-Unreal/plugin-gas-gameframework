// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFDamageableActor.h"

#include "AbilitySystemComponent.h"
#include "GGFGameplayTags.h"
#include "AbilitySystem/GGFDamageableAbilitySystem.h"

AGGFDamageableActor::AGGFDamageableActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UGGFDamageableAbilitySystem>(AbilitySystemName))
{

}

void AGGFDamageableActor::FellOutOfWorld(const UDamageType& dmgType)
{
    Super::FellOutOfWorld(dmgType);

    if(auto DamageableAbilitySystem = Cast<UGGFDamageableAbilitySystem>(GetAbilitySystem()))
    {
        if(HasAuthority())
        {
            DamageableAbilitySystem->AddLooseGameplayTag(State::Dead);
            DamageableAbilitySystem->AddReplicatedLooseGameplayTag(State::Dead);
        }
    }
    else
    {
        Super::FellOutOfWorld(dmgType);
    }
}

void AGGFDamageableActor::OnBindEvents()
{
    Super::OnBindEvents();

    // OnDead
    if(auto CastedAbilitySystem = Cast<UGGFDamageableAbilitySystem>(GetAbilitySystem()))
    {
        CastedAbilitySystem->OnDead.AddDynamic(this, &ThisClass::OnDead);
    }
}

void AGGFDamageableActor::OnDead_Implementation()
{

}
