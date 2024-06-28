// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFCharacterMovement.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GGFCharacterGameplayTags.h"
#include "GameFramework/Character.h"

UGGFCharacterMovement::UGGFCharacterMovement()
{
    // 초기화
    bWantsInitializeComponent = true;

    // 캐릭터 무브먼트 설정
    NavAgentProps.bCanCrouch = true;
    bCanWalkOffLedgesWhenCrouching = true;

    FallingTag = State::Locomotion::Falling;
    CrouchingTag = State::Locomotion::Crouching;
    MovingTag = State::Locomotion::Moving;

    // 일반 설정
    GravityScale = 1.5f;
    MaxAcceleration = 3000.f;
    BrakingFrictionFactor = 2.f;
    BrakingFriction = 1.f;
    SetCrouchedHalfHeight(54.f);
    bUseSeparateBrakingFriction = true;
    Mass = 400.f;

    // 걷기 설정
    MaxStepHeight = 25.f;
    GroundFriction = 10.f;
    MaxWalkSpeed = 400.f;

    // 점프 및 낙하 설정
    JumpZVelocity = 600.f;
    AirControl = 0.35f;
}

void UGGFCharacterMovement::InitializeComponent()
{
    Super::InitializeComponent();

    OwnerAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(PawnOwner);
}

void UGGFCharacterMovement::SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode)
{
    if(MovementMode != NewMovementMode && OwnerAbilitySystem.IsValid())
    {
        // Falling 게임플레이 태그 부착 혹은 제거
        if(NewMovementMode == MOVE_Falling)
            OwnerAbilitySystem->AddLooseGameplayTag(FallingTag);
        else if(MovementMode == MOVE_Falling)
            OwnerAbilitySystem->RemoveLooseGameplayTag(FallingTag);
    }

    Super::SetMovementMode(NewMovementMode, NewCustomMode);
}

void UGGFCharacterMovement::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
    if(OwnerAbilitySystem.IsValid())
    {
        const float GroundSpeed = FVector(Velocity.X, Velocity.Y, 0.f).Length();

        // 땅에서 최소한의 속도보다 빠르게 움직이고 있으며 가속도(입력)가 존재하는 경우 Moving 태그 부착
        if(IsMovingOnGround() && !GetCurrentAcceleration().IsNearlyZero() && GroundSpeed > MinAnalogWalkSpeed)
        {
            if(!OwnerAbilitySystem->HasMatchingGameplayTag(MovingTag))
                OwnerAbilitySystem->AddLooseGameplayTag(MovingTag);
        }
        else
        {
            if(OwnerAbilitySystem->HasMatchingGameplayTag(MovingTag))
                OwnerAbilitySystem->RemoveLooseGameplayTag(MovingTag);
        }
    }

    Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);
}

void UGGFCharacterMovement::Crouch(bool bClientSimulation)
{
    // Crouch 게임플레이 태그 부착
    if(OwnerAbilitySystem.IsValid())
    {
        OwnerAbilitySystem->AddLooseGameplayTag(CrouchingTag);
    }

    Super::Crouch(bClientSimulation);
}

void UGGFCharacterMovement::UnCrouch(bool bClientSimulation)
{
    // Crouch 게임플레이 태그 제거
    if(OwnerAbilitySystem.IsValid())
    {
        OwnerAbilitySystem->RemoveLooseGameplayTag(CrouchingTag);
    }

    Super::UnCrouch(bClientSimulation);
}

bool UGGFCharacterMovement::CanAttemptJump() const
{
    // 앉기 상태에서도 점프 가능
    return IsJumpAllowed() && (IsMovingOnGround() || IsFalling());
}

bool UGGFCharacterMovement::DoJump(bool bReplayingMoves)
{
    if ( CharacterOwner && CharacterOwner->CanJump() )
    {
        // 위 아래로 움직일 수 없는 경우 점프를 할 수 없습니다.
        if (!bConstrainToPlane || FMath::Abs(PlaneConstraintNormal.Z) != 1.f)
        {
            // 앉은 상태에서 점프를 하는 경우 먼저 UnCrouch를 호출합니다.
            if(IsCrouching()) bWantsToCrouch = false;

            // 중력 관련 처리
            if (HasCustomGravity())
            {
                FVector GravityRelativeVelocity = RotateWorldToGravity(Velocity);
                GravityRelativeVelocity.Z = FMath::Max<FVector::FReal>(GravityRelativeVelocity.Z, JumpZVelocity);
                Velocity = RotateGravityToWorld(GravityRelativeVelocity);
            }
            else
            {
                Velocity.Z = FMath::Max<FVector::FReal>(Velocity.Z, JumpZVelocity);
            }

            // Falling 모드로 변경
            SetMovementMode(MOVE_Falling, 0);

            return true;
        }
    }

    return false;
}
