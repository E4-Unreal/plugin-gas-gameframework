// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GEPlayerCharacterBase.h"

#include "EnhancedInputSubsystems.h"
#include "GEInputConfig.h"
#include "Character/Components/GEAbilityInputBinder.h"

AGEPlayerCharacterBase::AGEPlayerCharacterBase(const FObjectInitializer& ObjectInitializer)
{
    AbilityInputBinder = CreateDefaultSubobject<UGEAbilityInputBinder>(TEXT("AbilityInputBinder"));
}

void AGEPlayerCharacterBase::BeginPlay()
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

void AGEPlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    SetupEnhancedInputComponent(Cast<UEnhancedInputComponent>(PlayerInputComponent));
}

void AGEPlayerCharacterBase::SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent)
{
    // null 검사
    if(EnhancedInputComponent == nullptr) return;

    // 어빌리티 전용 입력 바인딩
    AbilityInputBinder->BindAbilityInput(EnhancedInputComponent);
}
