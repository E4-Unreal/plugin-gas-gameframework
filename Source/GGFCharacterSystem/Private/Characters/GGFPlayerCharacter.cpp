// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GGFPlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "GGFWeapon.h"
#include "AbilitySystem/GGFPlayerCharacterAbilitySystem.h"
#include "Components/GGFCharacterManager.h"
#include "Components/GGFCharacterMovement.h"
#include "Components/GGFCharacterSkinManager.h"
#include "Components/GGFCharacterStateMachine.h"
#include "Components/GGFEquipmentManager.h"
#include "Components/GGFInteractionManager.h"
#include "Input/GGFInputManager.h"
#include "Net/UnrealNetwork.h"

FName AGGFPlayerCharacter::EquipmentManagerName(TEXT("EquipmentManager"));
FName AGGFPlayerCharacter::CharacterManagerName(TEXT("CharacterManager"));
FName AGGFPlayerCharacter::SkinManagerName(TEXT("SkinManager"));
FName AGGFPlayerCharacter::InteractionManagerName(TEXT("InteractionManager"));

AGGFPlayerCharacter::AGGFPlayerCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer
    .SetDefaultSubobjectClass<UGGFCharacterMovement>(CharacterMovementComponentName)
    .SetDefaultSubobjectClass<UGGFPlayerCharacterAbilitySystem>(AbilitySystemName)
    .SetDefaultSubobjectClass<UGGFInputManager>(InputManagerName)
    .SetDefaultSubobjectClass<UGGFCharacterStateMachine>(GameplayStateMachineName))
{
    /* EquipmentManager */
    EquipmentManager = CreateDefaultSubobject<UGGFEquipmentManager>(EquipmentManagerName);

    /* CharacterManager */
    CharacterManager = CreateDefaultSubobject<UGGFCharacterManager>(CharacterManagerName);
    CharacterManager->SetCharacterMesh(GetMesh());

    /* SkinManager */
    SkinManager = CreateDefaultSubobject<UGGFCharacterSkinManager>(SkinManagerName);
    SkinManager->SetCharacterMesh(GetMesh());

    /* InteractionManager */
    InteractionManager = CreateDefaultSubobject<UGGFInteractionManager>(InteractionManagerName);
}

void AGGFPlayerCharacter::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
    Super::PreReplication(ChangedPropertyTracker);

    UpdateCharacterConfig();
}

void AGGFPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, CharacterConfig);
}

void AGGFPlayerCharacter::SetActorHiddenInGame(bool bNewHidden)
{
    Super::SetActorHiddenInGame(bNewHidden);

    if(bNewHidden)
    {
        EquipmentManager->Deactivate();
    }
    else
    {
        EquipmentManager->Activate(false);
    }
}

void AGGFPlayerCharacter::Restart()
{
    Super::Restart();

    // TODO EquipmentManager->Activate로 대체
    if(auto SelectedEquipment = GetEquipmentManager()->GetSelectedEquipment())
    {
        if(SelectedEquipment->Implements<UGGFEquipmentInterface>())
        {
            IGGFEquipmentInterface::Execute_Deactivate(SelectedEquipment);
            IGGFEquipmentInterface::Execute_Activate(SelectedEquipment);
        }
    }
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

/* GGFCharacterAnimationInterface */

void AGGFPlayerCharacter::SetAnimInstanceClass_Implementation(TSubclassOf<UAnimInstance> NewAnimInstanceClass)
{
    // 유효성 검사
    if(NewAnimInstanceClass == nullptr) return;

    // TODO 애님 인스턴스 클래스의 스켈레톤을 분석하여 1인칭, 3인칭 구분

    // 애님 인스턴스 클래스 변경
    GetMesh()->SetAnimInstanceClass(NewAnimInstanceClass);
}

void AGGFPlayerCharacter::PlayAnimMontage_Implementation(UAnimMontage* NewAnimMontage, float Duration)
{
    // 유효성 검사
    if(NewAnimMontage == nullptr) return;

    // TODO 애님 몽타주의 스켈레톤을 분석하여 1인칭, 3인칭 구분

    // 애님 몽타주 재생
    if(auto AnimInstance = GetMesh()->GetAnimInstance())
    {
        float PlayRate = FMath::IsNearlyZero(Duration) ? 1 : NewAnimMontage->GetPlayLength() / Duration;
        AnimInstance->Montage_Play(NewAnimMontage, PlayRate);
    }
}

void AGGFPlayerCharacter::UpdateCharacterConfig_Implementation()
{
    FGGFCharacterConfig NewCharacterConfig;
    NewCharacterConfig.CharacterID = GetCharacterManager()->GetCharacterID();
    NewCharacterConfig.SkinIDList = GetSkinManager()->GetCurrentSkinIDList();

    CharacterConfig = NewCharacterConfig;
}

void AGGFPlayerCharacter::OnRep_CharacterConfig(const FGGFCharacterConfig& OldCharacterConfig)
{
    // 캐릭터가 변경된 경우
    if(CharacterConfig.CharacterID != OldCharacterConfig.CharacterID)
    {
        // 캐릭터 설정 및 스킨 초기화
        GetCharacterManager()->SetCharacterByID(CharacterConfig.CharacterID);
        GetSkinManager()->Reset();

        // 파라곤처럼 불필요한 스켈레톤 숨기기
        HideBones();
    }

    // 캐릭터 스킨 설정
    for (int32 SkinID : CharacterConfig.SkinIDList)
    {
        // 스킨 설정
        GetSkinManager()->SetSkinByID(SkinID);

        // 파라곤처럼 불필요한 스켈레톤 숨기기
        HideBones();
    }
}

/* GGFCharacterInterface */

void AGGFPlayerCharacter::SetCharacter_Implementation(int32 NewCharacterID)
{
    ServerSetCharacter(NewCharacterID);
}

void AGGFPlayerCharacter::SetCharacterSkin_Implementation(int32 NewSkinID)
{
    ServerSetCharacterSkin(NewSkinID);
}

int32 AGGFPlayerCharacter::GetCharacterID_Implementation() const
{
    return GetCharacterManager()->GetCharacterID();
}

TArray<int32> AGGFPlayerCharacter::GetCharacterSkinIDList_Implementation() const
{
    return GetSkinManager()->GetCurrentSkinIDList();
}

void AGGFPlayerCharacter::ServerSetCharacter_Implementation(int32 NewCharacterID)
{
    // 캐릭터 설정 및 스킨 초기화
    GetCharacterManager()->SetCharacterByID(NewCharacterID);
    GetSkinManager()->Reset();

    // 파라곤처럼 불필요한 스켈레톤 숨기기
    HideBones();
}

void AGGFPlayerCharacter::ServerSetCharacterSkin_Implementation(int32 NewSkinID)
{
    // 스킨 설정
    GetSkinManager()->SetSkinByID(NewSkinID);

    // 파라곤처럼 불필요한 스켈레톤 숨기기
    HideBones();
}
