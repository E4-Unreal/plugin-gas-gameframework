// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/States/GECharacterState_Dead.h"

#include "GEGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Character/GEDefaultCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UGECharacterState_Dead::UGECharacterState_Dead()
{
    // Dead 태그가 부착된 이후 이 어빌리티가 발동되기 때문에 Blocking 태그 목록에서 제외해주어야 합니다.
    BlockAbilitiesWithTag.RemoveTag(GEGameplayTags::State::Dead);

    // 트리거 설정
    FAbilityTriggerData AbilityTriggerData;
    AbilityTriggerData.TriggerTag = GEGameplayTags::State::Dead;
    AbilityTriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagAdded;

    AbilityTriggers.Add(AbilityTriggerData);

    // 정책 설정
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;
    NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ServerOnlyExecution;
}

void UGECharacterState_Dead::OnEnter_Implementation(ACharacter* AvatarCharacter)
{
    /* 일반 캐릭터 죽음 설정 */
    // 플레이어 입력 비활성화
    if(APlayerController* PlayerController = Cast<APlayerController>(AvatarCharacter->Controller))
    {
        AvatarCharacter->DisableInput(PlayerController);
    }

    // 움직임 비활성화
    UCharacterMovementComponent* MovementComponent = AvatarCharacter->GetCharacterMovement();
    MovementComponent->DisableMovement();
    MovementComponent->StopMovementImmediately();

    // 스켈레탈 메시 콜리전 활성화
    AvatarCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    // 캡슐 컴포넌트 콜리전 비활성화
    AvatarCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    /* GEDefaultCharacter 캐릭터 전용 죽음 설정 */
    if(const AGEDefaultCharacter* GEDefaultCharacter = Cast<AGEDefaultCharacter>(AvatarCharacter))
    {
        // TODO 카메라 액션 설정 및 무기 메시를 3인칭 캐릭터에 부착
        UCameraComponent* Camera = GEDefaultCharacter->GetGameViewCamera();
        Camera->SetRelativeLocation(Camera->GetRelativeLocation() - Camera->GetForwardVector() * 300);

        GEDefaultCharacter->GetMesh()->SetOwnerNoSee(false);
        GEDefaultCharacter->GetFirstPersonArms()->SetOwnerNoSee(true);
        GEDefaultCharacter->GetFirstPersonLegs()->SetOwnerNoSee(true);
    }
}

void UGECharacterState_Dead::OnExit_Implementation(ACharacter* AvatarCharacter)
{
    /* 일반 캐릭터 부활 설정 */
    // 플레이어 입력 활성화
    if(APlayerController* PlayerController = Cast<APlayerController>(AvatarCharacter->Controller))
    {
        AvatarCharacter->EnableInput(PlayerController);
    }

    // 움직임 초기화
    AvatarCharacter->GetCharacterMovement()->SetDefaultMovementMode();

    // 스켈레탈 메시 콜리전 활성화
    AvatarCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    // 캡슐 컴포넌트 콜리전 활성화
    AvatarCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    /* GEDefaultCharacter 캐릭터 전용 부활 설정 */
    if(const AGEDefaultCharacter* GEDefaultCharacter = Cast<AGEDefaultCharacter>(AvatarCharacter))
    {
        UCameraComponent* Camera = GEDefaultCharacter->GetGameViewCamera();
        Camera->SetRelativeLocation(Camera->GetRelativeLocation() + Camera->GetForwardVector() * 300);

        GEDefaultCharacter->GetMesh()->SetOwnerNoSee(true);
        GEDefaultCharacter->GetFirstPersonArms()->SetOwnerNoSee(false);
        GEDefaultCharacter->GetFirstPersonLegs()->SetOwnerNoSee(false);
    }
}
