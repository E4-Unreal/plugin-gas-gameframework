// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/GGFCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Called when the game starts or when spawned
void AGGFCharacter::BeginPlay()
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

void AGGFCharacter::SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent)
{
    Super::SetupEnhancedInputComponent(EnhancedInputComponent);

    // 캐릭터 이동
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);

    // 카메라 회전
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);

    // 캐릭터 점프
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);

    // 캐릭터 앉기
    EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ThisClass::ToggleCrouch);
}

void AGGFCharacter::Move(const FInputActionValue& Value)
{
    // 컨트롤러만 사용할 수 있는 메서드입니다.
    if(Controller == nullptr) return;

    // 입력값 가져오기
    const FVector2D MovementVector = Value.Get<FVector2D>();

    // 회전값 가져오기
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // 이동 방향 계산
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    // 이동 입력
    AddMovementInput(ForwardDirection, MovementVector.Y);
    AddMovementInput(RightDirection, MovementVector.X);

    // 좌우 반복 뛰기 시 180도로 회전하는 오류 방지
    if(FMath::IsNearlyZero(MovementVector.Y) && !FMath::IsNearlyZero(MovementVector.X))
    {
        AddMovementInput(ForwardDirection, 0.0001f);
    }
}

void AGGFCharacter::Look(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // add yaw and pitch input to controller
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void AGGFCharacter::ToggleCrouch()
{
    if(bIsCrouched)
        UnCrouch();
    else
        Crouch();
}
