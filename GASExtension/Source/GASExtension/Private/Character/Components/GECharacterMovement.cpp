// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/GECharacterMovement.h"

#include "GameFramework/Character.h"

UGECharacterMovement::UGECharacterMovement()
{
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

bool UGECharacterMovement::CanAttemptJump() const
{
    // 앉기 상태에서도 점프 가능
    return IsJumpAllowed() && (IsMovingOnGround() || IsFalling());
}

bool UGECharacterMovement::DoJump(bool bReplayingMoves)
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
