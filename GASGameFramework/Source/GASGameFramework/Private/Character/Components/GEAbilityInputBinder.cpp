// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/GEAbilityInputBinder.h"

#include "AbilitySystemGlobals.h"
#include "GEAbilitySystemBase.h"
#include "GEInputConfig.h"

UGEAbilityInputBinder::UGEAbilityInputBinder()
{
    bWantsInitializeComponent = true;
}

void UGEAbilityInputBinder::InitializeComponent()
{
    Super::InitializeComponent();

    // 레퍼런스 할당
    AbilitySystem = Cast<UGEAbilitySystemBase>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()));

    // 어빌리티 전용 입력 에셋 등록
    RegisterAbilityInputConfig();
}

void UGEAbilityInputBinder::BindAbilityInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    // 유효성 검사
    if(EnhancedInputComponent == nullptr || !AbilitySystem.IsValid()) return;

    // 정상적으로 등록된 어빌리티 입력만 바인딩
    for (const auto& [InputAction, Tag] : RegisteredAbilityInput)
    {
        EnhancedInputComponent->BindAction(
            InputAction,
            ETriggerEvent::Started,
            this,
            &ThisClass::PressInputAction,
            InputAction.Get()
            );

        EnhancedInputComponent->BindAction(
            InputAction,
            ETriggerEvent::Completed,
            this,
            &ThisClass::ReleaseInputAction,
            InputAction.Get()
            );
    }
}

void UGEAbilityInputBinder::RegisterAbilityInputConfig()
{
    // null 검사
    if(AbilityInputConfig == nullptr) return;

    // InputConfig 캐싱
    const auto& InputWithGameplayTagList = AbilityInputConfig->GetInputWithGameplayTagList();
    RegisteredAbilityInput.Reserve(InputWithGameplayTagList.Num());
    for (const auto& InputWithGameplayTag : InputWithGameplayTagList)
    {
        // 지역 변수 선언
        UInputAction* InputAction = InputWithGameplayTag.InputAction;
        const FGameplayTag& InputTag = InputWithGameplayTag.InputTag;

        // 유효성 검사
        if(InputAction == nullptr || InputTag == FGameplayTag::EmptyTag) continue;

        // AbilityInputMap 등록
        RegisteredAbilityInput.Add(InputAction, InputTag);
    }
}

void UGEAbilityInputBinder::PressInputAction(UInputAction* InputAction)
{
    // 유효한 게임플레이 태그인지 검사
    const FGameplayTag& InputTag = RegisteredAbilityInput[InputAction];

    // Press Ability
    AbilitySystem->PressInputTag(InputTag);
}

void UGEAbilityInputBinder::ReleaseInputAction(UInputAction* InputAction)
{
    // 유효한 게임플레이 태그인지 검사
    const FGameplayTag& InputTag = RegisteredAbilityInput[InputAction];

    // Release Ability
    AbilitySystem->ReleaseInputTag(InputTag);
}
