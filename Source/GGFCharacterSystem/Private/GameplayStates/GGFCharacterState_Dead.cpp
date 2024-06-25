// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayStates/GGFCharacterState_Dead.h"

#include "AbilitySystemComponent.h"
#include "GEGameplayTags.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UGGFCharacterState_Dead::UGGFCharacterState_Dead()
{
    StateTag = State::Dead;
}

void UGGFCharacterState_Dead::OnEnter_Implementation()
{
    Super::OnEnter_Implementation();

    /* 모든 어빌리티 입력 Release 처리 */
    UAbilitySystemComponent* AbilitySystem = GetOwnerAbilitySystem();
    for (FGameplayAbilitySpec& ActivatableAbility : AbilitySystem->GetActivatableAbilities())
    {
        ActivatableAbility.InputPressed = false;
    }

    /* 일반 캐릭터 죽음 설정 */
    // 캐릭터 변수 선언
    ACharacter* Character = GetOwnerCharacter();

    // 플레이어 입력 비활성화
    if(APlayerController* PlayerController = Cast<APlayerController>(Character->Controller))
    {
        Character->DisableInput(PlayerController);
    }

    // 움직임 비활성화
    UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
    MovementComponent->DisableMovement();
    MovementComponent->StopMovementImmediately();

    // 스켈레탈 메시 콜리전 활성화
    Character->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    // 캡슐 컴포넌트 콜리전 비활성화
    Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // 3초 후 파괴
    Character->SetLifeSpan(3);
}

void UGGFCharacterState_Dead::OnExit_Implementation()
{
    Super::OnExit_Implementation();

    /* 일반 캐릭터 부활 설정 */
    // 캐릭터 변수 선언
    ACharacter* Character = GetOwnerCharacter();

    // 플레이어 입력 활성화
    if(APlayerController* PlayerController = Cast<APlayerController>(Character->Controller))
    {
        Character->EnableInput(PlayerController);
    }

    // 움직임 초기화
    Character->GetCharacterMovement()->SetDefaultMovementMode();

    // 스켈레탈 메시 콜리전 활성화
    Character->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    // 캡슐 컴포넌트 콜리전 활성화
    Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
