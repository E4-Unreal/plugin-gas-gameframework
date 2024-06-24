// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/GEPlayerAbilitySystem.h"

#include "GEGameplayTags.h"
#include "Abilities/GEGameplayAbility.h"
#include "Attributes/GGFHealthAttributes.h"

void UGEPlayerAbilitySystem::PressInputTag(FGameplayTag InputTag)
{
    // 디버깅을 위한 입력 태그를 추가합니다.
    if(!HasMatchingGameplayTag(InputTag)) AddLooseGameplayTag(InputTag);

    PressInputID(GetTypeHash(InputTag));
}

void UGEPlayerAbilitySystem::ReleaseInputTag(FGameplayTag InputTag)
{
    // 디버깅을 위한 입력 태그를 제거합니다.
    if(HasMatchingGameplayTag(InputTag)) RemoveLooseGameplayTag(InputTag);

    ReleaseInputID(GetTypeHash(InputTag));
}

void UGEPlayerAbilitySystem::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
    Super::OnGiveAbility(AbilitySpec);

    // 서버에서만 동작
    if(GetOwner()->HasAuthority())
    {
        // InputTag의 해시 값을 사용하여 InputID 설정
        if(AbilitySpec.Ability->Implements<UGEPlayerAbilityInterface>())
        {
            const FGameplayTag& InputTag = IGEPlayerAbilityInterface::Execute_GetAbilityInputTag(AbilitySpec.Ability);
            AbilitySpec.InputID = GetTypeHash(InputTag);
        }
    }
}

void UGEPlayerAbilitySystem::OnAbilitySpecDirtied(const FGameplayAbilitySpec& AbilitySpec)
{
    Super::OnAbilitySpecDirtied(AbilitySpec);

    if(AbilitySpec.Ability->Implements<UGEPlayerAbilityInterface>())
    {
        if(auto AbilityInstance = AbilitySpec.GetPrimaryInstance())
        {
            const auto AbilityInputTag = IGEPlayerAbilityInterface::Execute_GetAbilityInputTag(AbilitySpec.Ability);
            const auto AbilityInstanceInputTag = IGEPlayerAbilityInterface::Execute_GetAbilityInputTag(AbilityInstance);
            if(AbilityInputTag != AbilityInstanceInputTag)
            {
                FindAbilitySpecFromHandle(AbilitySpec.Handle)->InputID = GetTypeHash(AbilityInstanceInputTag);
            }
        }
    }
}
