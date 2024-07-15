// Fill out your copyright notice in the Description page of Project Settings.

#include "Animations/GGFCharacterAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Components/GGFFootstepManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UGGFCharacterAnimInstance::UGGFCharacterAnimInstance()
{
    /* 기본 설정 */

    LeftFootstepNotifyNames.Emplace("Footstep_Left");
    RightFootstepNotifyNames.Emplace("Footstep_Right");
}

void UGGFCharacterAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    // 레퍼런스 할당
    OwningCharacter = Cast<ACharacter>(GetOwningActor());
    if(OwningCharacter)
    {
        OwningCharacterMovement = OwningCharacter->GetCharacterMovement();
    }

    // 유효성 검사
    if(IsNotValid()) return;

    GetOwningCharacter()->bUseControllerRotationYaw = bUseControllerRotationYaw;
    GetOwningCharacterMovement()->bOrientRotationToMovement = !bUseControllerRotationYaw;
}

void UGGFCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

    // 유효성 검사
    if(IsNotValid()) return;

    // 애님 인스턴스 변수 계산
    FetchCharacterMovement(DeltaSeconds);
    CalculateVelocity(DeltaSeconds);
    CalculateAimOffset(DeltaSeconds);
}

void UGGFCharacterAnimInstance::CalculateVelocity(float DeltaSeconds)
{
    auto Character = GetOwningCharacter();
    auto CharacterMovement = GetOwningCharacterMovement();

    // 속도
    Velocity = CharacterMovement->GetLastUpdateVelocity();
    GroundSpeed = FVector(Velocity.X, Velocity.Y, 0.f).Length();
    bShouldMove = !CharacterMovement->GetCurrentAcceleration().IsNearlyZero() && GroundSpeed > 3.f;
    Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Character->GetActorRotation());
}

void UGGFCharacterAnimInstance::CalculateAimOffset(float DeltaSeconds)
{
    auto Character = GetOwningCharacter();

    // 에임 오프셋
    const FRotator TargetRotator = (Character->GetBaseAimRotation() - Character->GetActorRotation()).GetNormalized();
    const FRotator CurrentRotator = FRotator(PitchOffset, YawOffset, 0.f);
    const FRotator DesiredRotator = FMath::RInterpTo(CurrentRotator, TargetRotator, DeltaSeconds, InterpSpeed);

    PitchOffset = FMath::Clamp(DesiredRotator.Pitch, -90.f, 90.f);
    YawOffset = FMath::Clamp(DesiredRotator.Yaw, -90.f, 90.f);
    YawOffset += YawOffset - DesiredRotator.Yaw; // 초과한 각도만큼 다시 원복함으로써 -180 에서 180 으로 한 번에 넘어가는 것을 방지
}

void UGGFCharacterAnimInstance::FetchCharacterMovement(float DeltaSeconds)
{
    auto CharacterMovement = GetOwningCharacterMovement();

    // 캐릭터 무브먼트 상태 가져오기
    bFalling = CharacterMovement->IsFalling();
    bCrouching = CharacterMovement->IsCrouching();
}

bool UGGFCharacterAnimInstance::HandleNotify(const FAnimNotifyEvent& AnimNotifyEvent)
{
    HandleFootstepNotify(AnimNotifyEvent);
    
    return Super::HandleNotify(AnimNotifyEvent);
}

bool UGGFCharacterAnimInstance::HandleFootstepNotify(const FAnimNotifyEvent& AnimNotifyEvent)
{
    bool bResult = false;

    // TODO 인터페이스로 대체?
    if(LeftFootstepNotifyNames.Contains(AnimNotifyEvent.NotifyName))
    {
        // 왼발 스텝 이벤트 처리
        if(auto FootstepManager = Cast<UGGFFootstepManager>(GetOwningCharacter()->GetComponentByClass(UGGFFootstepManager::StaticClass())))
        {
            FootstepManager->SpawnLeftFootstepEffect();
            bResult = true;
        }
    }
    else if(RightFootstepNotifyNames.Contains(AnimNotifyEvent.NotifyName))
    {
        // 오른발 스텝 이벤트 처리
        if(auto FootstepManager = Cast<UGGFFootstepManager>(GetOwningCharacter()->GetComponentByClass(UGGFFootstepManager::StaticClass())))
        {
            FootstepManager->SpawnRightFootstepEffect();
            bResult = true;
        }
    }

    return bResult;
}
