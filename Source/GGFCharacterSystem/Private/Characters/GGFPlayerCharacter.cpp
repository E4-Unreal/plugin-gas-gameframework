// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GGFPlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/GGFPlayerAbilitySystem.h"
#include "Components/GGFCharacterManager.h"
#include "Components/GGFCharacterMovement.h"
#include "Components/GGFCharacterSkinManager.h"
#include "Components/GGFCharacterStateMachine.h"
#include "Components/GGFEquipmentManager.h"
#include "Input/GGFInputManager.h"
#include "Net/UnrealNetwork.h"

FName AGGFPlayerCharacter::EquipmentManagerName(TEXT("EquipmentManager"));
FName AGGFPlayerCharacter::CharacterManagerName(TEXT("CharacterManager"));
FName AGGFPlayerCharacter::SkinManagerName(TEXT("SkinManager"));

AGGFPlayerCharacter::AGGFPlayerCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer
    .SetDefaultSubobjectClass<UGGFCharacterMovement>(CharacterMovementComponentName)
    .SetDefaultSubobjectClass<UGGFPlayerAbilitySystem>(AbilitySystemName)
    .SetDefaultSubobjectClass<UGGFInputManager>(InputManagerName)
    .SetDefaultSubobjectClass<UGGFCharacterStateMachine>(GameplayStateMachineName))
{
    /* EquipmentManager */
    EquipmentManager = CreateDefaultSubobject<UGGFEquipmentManager>(EquipmentManagerName);

    /* CharacterManager */
    CharacterManager = CreateDefaultSubobject<UGGFCharacterManager>(CharacterManagerName);
    CharacterManager->SetMesh(GetMesh());

    /* SkinManager */
    SkinManager = CreateDefaultSubobject<UGGFCharacterSkinManager>(SkinManagerName);
    SkinManager->SetCharacterMesh(GetMesh());
}

void AGGFPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, CharacterConfig);
}

bool AGGFPlayerCharacter::CanJumpInternal_Implementation() const
{
    // 앉은 상태에서도 점프가 가능합니다.
    return JumpIsAllowedInternal();
}

bool AGGFPlayerCharacter::CanCrouch() const
{
    // 점프 상태에서는 앉기가 불가능합니다.
    return !GetCharacterMovement()->IsFalling() && Super::CanCrouch();
}

void AGGFPlayerCharacter::Move(const FInputActionValue& Value)
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

void AGGFPlayerCharacter::Look(const FInputActionValue& Value)
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

void AGGFPlayerCharacter::ToggleCrouch()
{
    if(bIsCrouched)
        UnCrouch();
    else
        Crouch();
}

void AGGFPlayerCharacter::NetMulticast_PlayMontage_Implementation(UAnimMontage* MontageToPlay)
{
    GetMesh()->GetAnimInstance()->Montage_Play(MontageToPlay);
}

/* GGFCharacterAnimationInterface */

void AGGFPlayerCharacter::PlayMontage_Implementation(UAnimMontage* MontageToPlay)
{
    NetMulticast_PlayMontage(MontageToPlay);
}

void AGGFPlayerCharacter::ChangeAnimInstance_Implementation(FGameplayTag EquipmentTag)
{
    if(AnimInstanceMap.Contains(EquipmentTag))
    {
        GetMesh()->SetAnimInstanceClass(AnimInstanceMap[EquipmentTag]);

        if(EquipMontageMap.Contains(EquipmentTag))
        {
            GetMesh()->GetAnimInstance()->Montage_Play(EquipMontageMap[EquipmentTag]);
        }
    }
}

void AGGFPlayerCharacter::SetCharacterConfig_Implementation(const FGGFCharacterConfig& NewCharacterConfig)
{
    const FGGFCharacterConfig& OldCharacterConfig = CharacterConfig;
    CharacterConfig = NewCharacterConfig;
    OnRep_CharacterConfig(OldCharacterConfig);
}

void AGGFPlayerCharacter::OnRep_CharacterConfig(const FGGFCharacterConfig& OldCharacterConfig)
{
    // 캐릭터가 변경된 경우
    if(CharacterConfig.CharacterID != OldCharacterConfig.CharacterID)
    {
        GetCharacterManager()->SetID(CharacterConfig.CharacterID);
        GetSkinManager()->Reset();
    }

    // 캐릭터 스킨 설정
    for (int32 SkinID : CharacterConfig.SkinIDList)
    {
        GetSkinManager()->SetSkinID(SkinID);
    }
}
