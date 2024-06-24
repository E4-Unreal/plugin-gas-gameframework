// Fill out your copyright notice in the Description page of Project Settings.

#include "Animations/GGFAnimInstanceBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

void UGGFAnimInstanceBase::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    OwningAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwningActor());
    if(OwningAbilitySystem)
    {
        // GameplayTagPropertyMap 매핑
        GameplayTagPropertyMap.Initialize(this, OwningAbilitySystem);
    }
}
