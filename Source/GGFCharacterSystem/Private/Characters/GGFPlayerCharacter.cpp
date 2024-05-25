// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GGFPlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "GGFDataSubsystem.h"
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

void AGGFPlayerCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 초기화
    Execute_SetCharacterID(this, DefaultCharacterID);
    for (int32 DefaultCharacterSkinID : DefaultCharacterSkinIDList)
    {
        Execute_SetCharacterSkinID(this, DefaultCharacterSkinID);
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
    else if(FGGFCharacterData* NewCharacterData = static_cast<FGGFCharacterData*>(UGGFDataSubsystem::GetDirectData(UGGFCharacterDefinition::StaticClass(), ID)))
    {
        return Execute_SetCharacterData(this, *NewCharacterData);
    }

    return false;
}

/* GGFCharacterSkinInterface */

bool AGGFPlayerCharacter::SetCharacterSkinData_Implementation(const FGGFCharacterSkinData& NewCharacterSkinData)
{
    // 입력 유효성 검사
    if(NewCharacterSkinData.IsNotValid()) return false;

    // 캐릭터 ID
    int32 CharacterID = CharacterDefinition && CharacterDefinition->IsValid() ? CharacterDefinition->GetID() : DefaultCharacterID;

    // 사용 가능한 캐릭터 목록에 존재하는지 확인
    if(!NewCharacterSkinData.AvailableCharacterIDList.IsEmpty() && !NewCharacterSkinData.AvailableCharacterIDList.Contains(CharacterID)) return false;

    // 사용 불가능한 캐릭터 목록에 존재하는지 확인
    if(!NewCharacterSkinData.ForbiddenCharacterIDList.IsEmpty() && NewCharacterSkinData.ForbiddenCharacterIDList.Contains(CharacterID)) return false;

    // 스킨 종류 확인 후 초기화
    switch (NewCharacterSkinData.SkinType)
    {
    case EGGFCharacterSkinType::Full:
        GetMesh()->SetSkeletalMesh(NewCharacterSkinData.SkeletalMesh);
        break;
    default:
        return false;
        break;
    }

    return true;
}

bool AGGFPlayerCharacter::SetCharacterSkinDefinition_Implementation(UGGFCharacterSkinDefinition* NewDefinition)
{
    // 입력 유효성 검사
    if(NewDefinition == nullptr || NewDefinition->IsNotValid()) return false;

    // 초기화
    if(Execute_SetCharacterSkinData(this, NewDefinition->GetData()))
    {
        // 데이터 에셋 교체
        CharacterSkinDefinitionMap.Emplace(NewDefinition->GetData().SkinType, NewDefinition);

        return true;
    }

    return false;
}

bool AGGFPlayerCharacter::SetCharacterSkinID_Implementation(int32 ID)
{
    if(GetGameInstance())
    {
        UGGFDataSubsystem* DataSubsystem = GetGameInstance()->GetSubsystem<UGGFDataSubsystem>();
        UGGFCharacterSkinDefinition* NewCharacterSkinDefinition = Cast<UGGFCharacterSkinDefinition>(DataSubsystem->GetOrCreateDefinition(UGGFCharacterSkinDefinition::StaticClass(), ID));

        return Execute_SetCharacterSkinDefinition(this, NewCharacterSkinDefinition);
    }
    else if(FGGFCharacterSkinData* NewCharacterSkinData = static_cast<FGGFCharacterSkinData*>(UGGFDataSubsystem::GetDirectData(UGGFCharacterSkinDefinition::StaticClass(), ID)))
    {
        return Execute_SetCharacterSkinData(this, *NewCharacterSkinData);
    }

    return false;
}
