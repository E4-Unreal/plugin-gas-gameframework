// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFGA_Interact.h"

#include "Components/GGFInteractionManager.h"
#include "GGFInteractionGameplayTags.h"

using namespace GGFGameplayTags;

UGGFGA_Interact::UGGFGA_Interact()
{
    InputTag = Input::Interact;
}

void UGGFGA_Interact::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

    InteractionManager = ActorInfo->AvatarActor->GetComponentByClass<UGGFInteractionManager>();
    if(!InteractionManager.IsValid()) bValid = false;
}

void UGGFGA_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if(InteractionManager.IsValid())
    {
        InteractionManager->Interact();
    }
}

bool UGGFGA_Interact::InternalCanActivate()
{
    if(InteractionManager.IsValid())
    {
        return InteractionManager->CanInteract();
    }

    return false;
}
