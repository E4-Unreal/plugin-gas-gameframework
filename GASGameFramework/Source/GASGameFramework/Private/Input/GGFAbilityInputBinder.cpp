// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/GGFAbilityInputBinder.h"

#include "AbilitySystemGlobals.h"
#include "GGFAbilitySystemBase.h"
#include "Input/GGFInputConfig.h"

UGGFAbilityInputBinder::UGGFAbilityInputBinder()
{
    bWantsInitializeComponent = true;
}

void UGGFAbilityInputBinder::InitializeComponent()
{
    Super::InitializeComponent();

    // 레퍼런스 할당
    AbilitySystem = Cast<UGGFAbilitySystemBase>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()));

    // 어빌리티 전용 입력 에셋 등록
    RegisterAbilityInputConfig();
}

void UGGFAbilityInputBinder::BindAbilityInput(UEnhancedInputComponent* EnhancedInputComponent)
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

void UGGFAbilityInputBinder::RegisterAbilityInputConfig()
{
    // null 검사
    if(AbilityInputConfig == nullptr) return;

    // InputConfig 캐싱
    const auto& AbilityInputActions = AbilityInputConfig->GetAbilityInputActions();
    RegisteredAbilityInput.Reserve(AbilityInputActions.Num());
    for (const auto& AbilityInputAction : AbilityInputActions)
    {
        // 지역 변수 선언
        UInputAction* InputAction = AbilityInputAction.InputAction;
        const FGameplayTag& InputTag = AbilityInputAction.InputTag;

        // 유효성 검사
        if(InputAction == nullptr || InputTag == FGameplayTag::EmptyTag) continue;

        // AbilityInputMap 등록
        RegisteredAbilityInput.Add(InputAction, InputTag);
    }
}

void UGGFAbilityInputBinder::PressInputAction(UInputAction* InputAction)
{
    // 유효한 게임플레이 태그인지 검사
    const FGameplayTag& InputTag = RegisteredAbilityInput[InputAction];

    // Press Ability
    AbilitySystem->PressInputTag(InputTag);
}

void UGGFAbilityInputBinder::ReleaseInputAction(UInputAction* InputAction)
{
    // 유효한 게임플레이 태그인지 검사
    const FGameplayTag& InputTag = RegisteredAbilityInput[InputAction];

    // Release Ability
    AbilitySystem->ReleaseInputTag(InputTag);
}
