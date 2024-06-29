// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFTriggerComponent.h"

#include "Interfaces/GGFActivatableInterface.h"
#include "Logging.h"

void UGGFTriggerComponent::ToggleActivateTargets()
{
    if(IsActivated())
    {
        DeactivateTargets();
    }
    else
    {
        ActivateTargets();
    }
}

void UGGFTriggerComponent::ActivateTargets()
{
    if(bShouldToggle && bActivated) return;
    bActivated = true;

    for (auto Target : Targets)
    {
        if(!Target)
        {
#if WITH_EDITOR
            LOG_ACTOR_COMPONENT_DETAIL(Error, TEXT("Targets에 null 값이 포함되어 있습니다."))
#endif
            continue;
        }

        if(Target->Implements<UGGFActivatableInterface>())
        {
            IGGFActivatableInterface::Execute_Activate(Target, GetOwner());
#if WITH_EDITOR
            LOG_ACTOR_COMPONENT_DETAIL(Log, TEXT("Try Activate %s"), *Target->GetName())
#endif
        }
    }
}

void UGGFTriggerComponent::DeactivateTargets()
{
    if(bShouldToggle && !bActivated) return;
    bActivated = false;

    for (auto Target : Targets)
    {
        if(Target->Implements<UGGFActivatableInterface>())
        {
            IGGFActivatableInterface::Execute_Deactivate(Target, GetOwner());
#if WITH_EDITOR
            LOG_ACTOR_COMPONENT_DETAIL(Log, TEXT("Try Deactivate %s"), *Target->GetName())
#endif
        }
    }
}
