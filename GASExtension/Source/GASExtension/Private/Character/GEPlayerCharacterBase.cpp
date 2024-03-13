// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GEPlayerCharacterBase.h"

#include "EnhancedInputSubsystems.h"
#include "GEAbilitySystemBase.h"
#include "GEInputConfig.h"

void AGEPlayerCharacterBase::BeginPlay()
{
    Super::BeginPlay();

    AddMappingContext(AbilityInputMappingContext);
}

void AGEPlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    SetupEnhancedInputComponent(CastChecked<UEnhancedInputComponent>(PlayerInputComponent));
}

void AGEPlayerCharacterBase::SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent)
{
    // null 검사
    if(EnhancedInputComponent == nullptr) return;

    // AbilityInputConfig 설정 및 입력 액션 바인딩
    SetupAbilityInputConfig(EnhancedInputComponent);
}

void AGEPlayerCharacterBase::AddMappingContext(UInputMappingContext* InputMappingContext, int32 Priority)
{
    if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputMappingContext, Priority);
        }
    }
}

void AGEPlayerCharacterBase::SetupAbilityInputConfig(UEnhancedInputComponent* EnhancedInputComponent)
{
    // null 검사
    if(AbilityInputConfig == nullptr) return;

    // InputConfig 캐싱
    const auto& InputWithGameplayTagList = AbilityInputConfig->GetInputWithGameplayTagList();
    AbilityInputMap.Reserve(InputWithGameplayTagList.Num());
    for (const auto& InputWithGameplayTag : InputWithGameplayTagList)
    {
        // 지역 변수 선언
        UInputAction* InputAction = InputWithGameplayTag.InputAction;
        const FGameplayTag& InputTag = InputWithGameplayTag.InputTag;

        // AbilityInputMap 등록
        AbilityInputMap.Add(InputAction, InputTag);

        // 입력 이벤트 바인딩
        EnhancedInputComponent->BindAction(
            InputAction,
            ETriggerEvent::Started,
            this,
            &ThisClass::OnInputActionPressed,
            InputAction
            );

        EnhancedInputComponent->BindAction(
            InputAction,
            ETriggerEvent::Completed,
            this,
            &ThisClass::OnInputActionReleased,
            InputAction
            );
    }
}

void AGEPlayerCharacterBase::OnInputActionPressed(UInputAction* InputAction)
{
    // 등록된 입력 액션인지 검사
    if(!AbilityInputMap.Contains(InputAction)) return;

    // 유효한 게임플레이 태그인지 검사
    const FGameplayTag& InputTag = AbilityInputMap[InputAction];
    if(InputTag == FGameplayTag::EmptyTag) return;

    // Ability Press
    GetAbilitySystem()->PressInputTag(InputTag);
}

void AGEPlayerCharacterBase::OnInputActionReleased(UInputAction* InputAction)
{
    // 등록된 입력 액션인지 검사
    if(!AbilityInputMap.Contains(InputAction)) return;

    // 유효한 게임플레이 태그인지 검사
    const FGameplayTag& InputTag = AbilityInputMap[InputAction];
    if(InputTag == FGameplayTag::EmptyTag) return;

    // Ability Release
    GetAbilitySystem()->ReleaseInputTag(InputTag);
}
