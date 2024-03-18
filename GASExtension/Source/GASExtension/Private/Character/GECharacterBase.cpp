// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GECharacterBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GEAbilitySystemBase.h"
#include "Character/GEStateMachine.h"
#include "Character/Components/GEAbilityInputBinder.h"
#include "Character/Components/GECharacterMovement.h"

FName AGECharacterBase::AbilitySystemComponentName(TEXT("AbilitySystem"));
FName AGECharacterBase::StateMachineName(TEXT("StateMachine"));

AGECharacterBase::AGECharacterBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer
    .SetDefaultSubobjectClass<UGECharacterMovement>(CharacterMovementComponentName))
{
    /* 서브 오브젝트 생성 */
    AbilitySystem = CreateDefaultSubobject<UGEAbilitySystemBase>(AbilitySystemComponentName);
    StateMachine = CreateDefaultSubobject<UGEStateMachine>(StateMachineName);
    AbilityInputBinder = CreateDefaultSubobject<UGEAbilityInputBinder>(TEXT("AbilityInputBinder"));
}

void AGECharacterBase::BeginPlay()
{
    Super::BeginPlay();

    // 기본 입력 매핑 컨텍스트 추가
    if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            for (const auto& MappingContext : DefaultMappingContexts)
            {
                Subsystem->AddMappingContext(MappingContext, 0);
            }
        }
    }
}

void AGECharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    SetupEnhancedInputComponent(Cast<UEnhancedInputComponent>(PlayerInputComponent));
}

void AGECharacterBase::SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent)
{
    // null 검사
    if(EnhancedInputComponent == nullptr) return;

    // 어빌리티 전용 입력 바인딩
    AbilityInputBinder->BindAbilityInput(EnhancedInputComponent);
}

bool AGECharacterBase::CanJumpInternal_Implementation() const
{
    // 앉은 상태에서도 점프가 가능합니다.
    return JumpIsAllowedInternal();
}

bool AGECharacterBase::CanCrouch() const
{
    // 점프 상태에서는 앉기가 불가능합니다.
    return !GetCharacterMovement()->IsFalling() && Super::CanCrouch();
}
