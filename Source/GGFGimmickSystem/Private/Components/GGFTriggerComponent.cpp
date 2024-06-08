// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFTriggerComponent.h"

#include "Interfaces/GGFActivationInterface.h"
#include "Logging.h"

void UGGFTriggerComponent::ActivateTargets()
{
    for (auto Target : Targets)
    {
        if(!Target)
        {
#if WITH_EDITOR
            LOG_ACTOR_COMPONENT_DETAIL(Error, TEXT("Targets에 null 값이 포함되어 있습니다."))
#endif
            continue;
        }

        if(Target->Implements<UGGFActivationInterface>())
        {
            IGGFActivationInterface::Execute_Activate(Target, GetOwner());
#if WITH_EDITOR
            LOG_ACTOR_COMPONENT_DETAIL(Log, TEXT("Try Activate %s"), *Target->GetName())
#endif
        }
    }
}

void UGGFTriggerComponent::DeactivateTargets()
{
    for (auto Target : Targets)
    {
        if(Target->Implements<UGGFActivationInterface>())
        {
            IGGFActivationInterface::Execute_Deactivate(Target, GetOwner());
#if WITH_EDITOR
            LOG_ACTOR_COMPONENT_DETAIL(Log, TEXT("Try Deactivate %s"), *Target->GetName())
#endif
        }
    }
}
