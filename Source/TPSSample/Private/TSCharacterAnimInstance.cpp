// Fill out your copyright notice in the Description page of Project Settings.

#include "TSCharacterAnimInstance.h"

#include "GGFEquipment.h"
#include "KismetAnimationLibrary.h"
#include "Components/GGFEquipmentManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTSCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

    // 유효성 검사
    if(IsNotValid()) return;

    /* 변수 할당 */

    ACharacter* Character = GetOwningCharacter();
    UCharacterMovementComponent* CharacterMovement = GetOwningCharacterMovement();

    // 속도
    Velocity = CharacterMovement->GetLastUpdateVelocity();
    GroundSpeed = FVector(Velocity.X, Velocity.Y, 0.f).Length();
    bShouldMove = !CharacterMovement->GetCurrentAcceleration().IsNearlyZero() && GroundSpeed > 3.f;
    Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Character->GetActorRotation());

    // 에임 오프셋
    const FRotator TargetRotator = (Character->GetBaseAimRotation() - Character->GetActorRotation()).GetNormalized();
    const FRotator CurrentRotator = FRotator(PitchOffset, YawOffset, 0.f);
    const FRotator DesiredRotator = FMath::RInterpTo(CurrentRotator, TargetRotator, DeltaSeconds, InterpSpeed);

    PitchOffset = FMath::Clamp(DesiredRotator.Pitch, -90.f, 90.f);
    YawOffset = FMath::Clamp(DesiredRotator.Yaw, -90.f, 90.f);
    YawOffset += YawOffset - DesiredRotator.Yaw; // 초과한 각도만큼 다시 원복함으로써 -180 에서 180 으로 한 번에 넘어가는 것을 방지

    // LeftHand IK

    bCanUseLeftHandTransform = false;
    if(auto EquipmentManager = GetOwningActor()->GetComponentByClass<UGGFEquipmentManager>())
    {
        if(auto SelectedEquipment = Cast<AGGFEquipment>(EquipmentManager->GetSelectedEquipment()))
        {
            if(SelectedEquipment->GetSkeletalMesh()->DoesSocketExist(LeftHandSocketName))
            {
                LeftHandTransform = SelectedEquipment->GetSkeletalMesh()->GetSocketTransform(LeftHandSocketName, RTS_ParentBoneSpace);
                bCanUseLeftHandTransform = true;
            }
        }
    }
    bCanUseLeftHandTransform = bCanUseLeftHandTransform && FMath::IsNearlyZero(GetCurveValue(DisableLeftHandIKCurveName));
}
