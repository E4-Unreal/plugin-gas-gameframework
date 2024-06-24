// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/GGFGameplayEffect.h"

#include "GameplayEffectComponents/TargetTagRequirementsGameplayEffectComponent.h"
#include "GGFGameplayTags.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"

UGGFGameplayEffect::UGGFGameplayEffect()
{
    /* TargetTagRequirementsComponent */
    TargetTagRequirementsComponent = CreateDefaultSubobject<UTargetTagRequirementsGameplayEffectComponent>(TEXT("TargetTagRequirementsComponent"));
    TargetTagRequirementsComponent->ApplicationTagRequirements.IgnoreTags.AddTagFast(State::Dead);
    TargetTagRequirementsComponent->OngoingTagRequirements.IgnoreTags.AddTagFast(State::Dead);
    TargetTagRequirementsComponent->RemovalTagRequirements.RequireTags.AddTagFast(State::Dead);

    /* TargetTagsGameplayEffectComponent */
    TargetTagsGameplayEffectComponent = CreateDefaultSubobject<UTargetTagsGameplayEffectComponent>(TEXT("TargetTagsGameplayEffectComponent"));

    /* 컴포넌트 등록 */
    GEComponents.Emplace(TargetTagRequirementsComponent.Get());
    GEComponents.Emplace(TargetTagsGameplayEffectComponent.Get());
}

UTargetTagRequirementsGameplayEffectComponent* UGGFGameplayEffect::
GetOrFindTargetTagRequirementsComponent()
{
    return GetOrFindComponent(TargetTagRequirementsComponent).Get();
}

UTargetTagsGameplayEffectComponent* UGGFGameplayEffect::GetOrFindTargetTagsGameplayEffectComponent()
{
    return GetOrFindComponent(TargetTagsGameplayEffectComponent).Get();
}

template <class T>
TWeakObjectPtr<T> UGGFGameplayEffect::GetOrFindComponent(TWeakObjectPtr<T>& Component) const
{
    if(!Component.IsValid())
    {
        for (auto GEComponent : GEComponents)
        {
            if(GEComponent->GetClass()->IsChildOf(T::StaticClass()))
            {
                Component = CastChecked<T>(GEComponent);
            }
        }
    }

    return Component;
}
