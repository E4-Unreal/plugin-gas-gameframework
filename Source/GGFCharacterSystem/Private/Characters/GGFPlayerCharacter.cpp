// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GGFPlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "GGFDataSubsystem.h"
#include "AbilitySystem/GGFPlayerAbilitySystem.h"
#include "Components/GGFCharacterMovement.h"
#include "Components/GGFCharacterSkinManager.h"
#include "Components/GGFCharacterStateMachine.h"
#include "Components/GGFEquipmentManager.h"
#include "Data/GGFCharacterDataSubsystem.h"
#include "Input/GGFInputManager.h"

FName AGGFPlayerCharacter::EquipmentManagerName(TEXT("EquipmentManager"));
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

    /* SkinManager */
    SkinManager = CreateDefaultSubobject<UGGFCharacterSkinManager>(SkinManagerName);
    SkinManager->SetCharacterMesh(GetMesh());
}

void AGGFPlayerCharacter::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    // 초기화
    Execute_SetCharacterID(this, DefaultCharacterID);
}

#if WITH_EDITOR
void AGGFPlayerCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    FName PropertyName = PropertyChangedEvent.GetMemberPropertyName();
    if(PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, DefaultCharacterID))
    {
        if(FGGFCharacterData* NewCharacterData = UGGFCharacterDataSubsystem::GetDirectCharacterData(DefaultCharacterID))
        {
            Execute_SetCharacterData(this, *NewCharacterData);
        }
    }

    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif


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

bool AGGFPlayerCharacter::SetCharacterData_Implementation(const FGGFCharacterData& NewCharacterData)
{
    // 입력 유효성 검사
    if(NewCharacterData.IsNotValid()) return false;

    // 캐릭터 설정
    USkeletalMeshComponent* CharacterMesh = GetMesh();
    CharacterMesh->SetSkeletalMesh(NewCharacterData.SkeletalMesh);
    CharacterMesh->SetAnimInstanceClass(NewCharacterData.AnimInstanceClass);

    return true;
}

bool AGGFPlayerCharacter::SetCharacterDefinition_Implementation(UGGFCharacterDefinition* NewDefinition)
{
    // 입력 유효성 검사
    if(NewDefinition == nullptr || NewDefinition->IsNotValid()) return false;

    // 초기화
    if(Execute_SetCharacterData(this, NewDefinition->GetData()))
    {
        // 데이터 에셋 교체
        CharacterDefinition = NewDefinition;

        return true;
    }

    return false;
}

bool AGGFPlayerCharacter::SetCharacterID_Implementation(int32 ID)
{
    if(GetGameInstance())
    {
        UGGFDataSubsystem* DataSubsystem = GetGameInstance()->GetSubsystem<UGGFDataSubsystem>();
        UGGFCharacterDefinition* NewCharacterDefinition = Cast<UGGFCharacterDefinition>(DataSubsystem->GetOrCreateDefinition(UGGFCharacterDefinition::StaticClass(), ID));

        return Execute_SetCharacterDefinition(this, NewCharacterDefinition);
    }

    return false;
}
