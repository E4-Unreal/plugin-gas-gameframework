// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/GGFGameplayEffect.h"

#include "GameplayEffectComponents/TargetTagRequirementsGameplayEffectComponent.h"
#include "GGFGameplayTags.h"

UGGFGameplayEffect::UGGFGameplayEffect()
{
    TargetTagRequirementsComponent = CreateDefaultSubobject<UTargetTagRequirementsGameplayEffectComponent>(TEXT("TargetTagRequirements"));
    TargetTagRequirementsComponent->ApplicationTagRequirements.IgnoreTags.AddTagFast(State::Dead);
    TargetTagRequirementsComponent->OngoingTagRequirements.IgnoreTags.AddTagFast(State::Dead);
    TargetTagRequirementsComponent->RemovalTagRequirements.RequireTags.AddTagFast(State::Dead);

    GEComponents.Emplace(TargetTagRequirementsComponent.Get());
}

TWeakObjectPtr<UTargetTagRequirementsGameplayEffectComponent> UGGFGameplayEffect::
GetOrFindTargetTagRequirementsComponent()
{
    if(!TargetTagRequirementsComponent.IsValid())
    {
        for (auto GEComponent : GEComponents)
        {
            if(GEComponent->GetClass()->IsChildOf(UTargetTagRequirementsGameplayEffectComponent::StaticClass()))
            {
                TargetTagRequirementsComponent = CastChecked<UTargetTagRequirementsGameplayEffectComponent>(GEComponent);
            }
        }
    }

    return TargetTagRequirementsComponent;
}
