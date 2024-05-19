// Fill out your copyright notice in the Description page of Project Settings.

#include "Animations/GEAnimInstance.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

void UGEAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwningActor());
    if(AbilitySystem.IsValid())
    {
        // GameplayTagPropertyMap 매핑
        GameplayTagPropertyMap.Initialize(this, AbilitySystem.Get());
    }
}
