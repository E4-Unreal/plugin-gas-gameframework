// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GGFPlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/GGFPlayerAbilitySystem.h"
#include "Components/GGFCharacterMovement.h"
#include "Components/GGFCharacterStateMachine.h"
#include "Components/GGFEquipmentManager.h"
#include "Input/GGFInputManager.h"

FName AGGFPlayerCharacter::EquipmentManagerName(TEXT("EquipmentManager"));

AGGFPlayerCharacter::AGGFPlayerCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer
    .SetDefaultSubobjectClass<UGGFCharacterMovement>(CharacterMovementComponentName)
    .SetDefaultSubobjectClass<UGGFPlayerAbilitySystem>(AbilitySystemName)
    .SetDefaultSubobjectClass<UGGFInputManager>(InputManagerName)
    .SetDefaultSubobjectClass<UGGFCharacterStateMachine>(GameplayStateMachineName))
{
    /* EquipmentManager */
    EquipmentManager = CreateDefaultSubobject<UGGFEquipmentManager>(EquipmentManagerName);
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

/* GGFCharacterInterface */

bool AGGFPlayerCharacter::SetCharacterDefinition_Implementation(UGGFCharacterDefinition* NewDefinition)
{
    // 입력 유효성 검사
    if(NewDefinition == nullptr) return false;

    // 데이터 에셋 교체
    CharacterDefinition = NewDefinition;

    // 캐릭터 설정
    const FGGFCharacterData& Data = CharacterDefinition->GetData();
    USkeletalMeshComponent* CharacterMesh = GetMesh();
    CharacterMesh->SetSkeletalMesh(Data.SkeletalMesh);
    CharacterMesh->SetAnimInstanceClass(Data.AnimInstanceClass);

    return true;
}

bool AGGFPlayerCharacter::SetCharacterSkinDefinition_Implementation(UGGFCharacterSkinDefinition* NewDefinition)
{
    // 입력 유효성 검사
    if(NewDefinition == nullptr) return false;

    // 데이터 가져오기
    const FGGFCharacterData& CharacterData = CharacterDefinition->GetData();
    const FGGFCharacterSkinData& SkinData = NewDefinition->GetData();

    /* 호환성 검사 */

    // 사용 가능한 캐릭터 목록에 존재하는지 확인
    if(!SkinData.AvailableCharacterIDList.IsEmpty() && !SkinData.AvailableCharacterIDList.Contains(CharacterData.ID)) return false;

    // 사용 불가능한 캐릭터 목록에 존재하는지 확인
    if(!SkinData.ForbiddenCharacterIDList.IsEmpty() && SkinData.ForbiddenCharacterIDList.Contains(CharacterData.ID)) return false;

    /* 설정 */

    // 스킨 종류 확인
    switch (SkinData.SkinType)
    {
    case EGGFCharacterSkinType::Full:
        CharacterSkinDefinitionMap.Emplace(EGGFCharacterSkinType::Full, NewDefinition);
        GetMesh()->SetSkeletalMesh(SkinData.SkeletalMesh);
        break;
    default:
        return false;
        break;
    }

    return true;
}
