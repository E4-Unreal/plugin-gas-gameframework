// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GEAnimInstance.h"

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

        // 게임플레이 태그 이벤트 바인딩
        for (const auto& Tag : TagsToRegister)
        {
            FOnGameplayEffectTagCountChanged& Delegate = AbilitySystem->RegisterGameplayTagEvent(Tag);
            Delegate.AddUObject(this, &ThisClass::OnGameplayEffectTagCountChanged_Event);
        }
    }
}

void UGEAnimInstance::OnGameplayEffectTagCountChanged_Event(const FGameplayTag Tag, int32 NewCount)
{
    // TODO 자손 클래스에서 게임플레이 태그 이벤트를 변수와 바인딩
}
