// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFTriggerComponent.h"

#include "Interfaces/GGFActivatableInterface.h"
#include "Logging.h"

void UGGFTriggerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    if(bIncludeOwner) TargetsToActivate.Emplace(GetOwner());
}

void UGGFTriggerComponent::ToggleTargets(AActor* Instigator)
{
    if(bTriggered)
    {
        DeactivateTargets(Instigator);
    }
    else
    {
        ActivateTargets(Instigator);
    }
}

void UGGFTriggerComponent::ActivateTargets(AActor* Instigator)
{
    if(!bCanRetrigger && bTriggered) return;
    bTriggered = true;

    for (auto Target : TargetsToActivate)
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
            IGGFActivatableInterface::Execute_TryActivate(Target, GetOwner(), Instigator);
#if WITH_EDITOR
            LOG_ACTOR_COMPONENT_DETAIL(Log, TEXT("Try Activate %s"), *Target->GetName())
#endif
        }
    }
}

void UGGFTriggerComponent::DeactivateTargets(AActor* Instigator)
{
    if(!bTriggered) return;
    bTriggered = false;

    for (auto Target : TargetsToActivate)
    {
        if(Target->Implements<UGGFActivatableInterface>())
        {
            IGGFActivatableInterface::Execute_TryDeactivate(Target, GetOwner(), Instigator);
#if WITH_EDITOR
            LOG_ACTOR_COMPONENT_DETAIL(Log, TEXT("Try Deactivate %s"), *Target->GetName())
#endif
        }
    }
}
