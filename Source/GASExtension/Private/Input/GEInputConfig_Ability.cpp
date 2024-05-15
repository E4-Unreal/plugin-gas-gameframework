// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/GEInputConfig_Ability.h"

#include "AbilitySystemGlobals.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystem/GEPlayerAbilitySystem.h"

void UGEInputConfig_Ability::OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    // AbilitySystem 유효성 검사
    UGEPlayerAbilitySystem* AbilitySystem = Cast<UGEPlayerAbilitySystem>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(EnhancedInputComponent->GetOwner()));
    if(AbilitySystem == nullptr) return;

    // 어빌리티 입력 바인딩
    for (const auto& [InputAction, InputTag] : AbilityInputActions)
    {
        // 유효성 검사
        if(InputAction == nullptr || !InputTag.IsValid()) continue;

        // TODO 매개변수를 FGameplayTag 대신 const FGameplayTag& 형식으로 사용하는 방법이 없을까?
        // PressInputTag 바인딩
        EnhancedInputComponent->BindAction(
            InputAction,
            ETriggerEvent::Started,
            AbilitySystem,
            &UGEPlayerAbilitySystem::PressInputTag,
            InputTag
            );

        // ReleaseInputTag 바인딩
        EnhancedInputComponent->BindAction(
            InputAction,
            ETriggerEvent::Completed,
            AbilitySystem,
            &UGEPlayerAbilitySystem::ReleaseInputTag,
            InputTag
            );
    }
}
