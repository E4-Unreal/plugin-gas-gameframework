// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/States/GGFCSA_Dead.h"

#include "AbilitySystemComponent.h"
#include "GEGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Character/GGFDefaultCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UGGFCSA_Dead::UGGFCSA_Dead()
{
    /* 태그 설정 */
    using namespace GEGameplayTags;

    // 죽은 상태는 절대적이기 때문에 어떠한 태그도 Blocking 할 수 없습니다.
    // 무적 상태를 도입하고 싶은 경우에는 체력을 1로 유지하는 등의 방법을 고려해주세요.
    ActivationBlockedTags.Reset();

    // Cancel 태그 설정
    BlockAbilitiesWithTag.AddTagFast(Action::Action); // 죽은 상태에서 모든 행동은 중지됩니다.
    CancelAbilitiesWithTag.AddTagFast(Action::Action);

    /* 트리거 설정 */
    FAbilityTriggerData AbilityTriggerData;
    AbilityTriggerData.TriggerTag = State::Dead;
    AbilityTriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagAdded;

    AbilityTriggers.Add(AbilityTriggerData);

    /* 정책 설정 */
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;
    NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ServerOnlyExecution;
}

void UGGFCSA_Dead::OnEnter_Implementation()
{
    // TODO Stun, KnockDown 등의 상태에서도 사용되기 때문에 공통 클래스가 필요
    /* 모든 어빌리티 입력 Release 처리 */
    TArray<FGameplayAbilitySpec>& ActivatableAbilities = CurrentActorInfo->AbilitySystemComponent->GetActivatableAbilities();
    for (FGameplayAbilitySpec& ActivatableAbility : ActivatableAbilities)
    {
        ActivatableAbility.InputPressed = false;
    }

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

    /* GGFDefaultCharacter 캐릭터 전용 죽음 설정 */
    if(const AGGFDefaultCharacter* GGFDefaultCharacter = Cast<AGGFDefaultCharacter>(AvatarCharacter))
    {
        // TODO 카메라 액션 설정 및 무기 메시를 3인칭 캐릭터에 부착
        UCameraComponent* Camera = GGFDefaultCharacter->GetGameViewCamera();
        Camera->SetRelativeLocation(Camera->GetRelativeLocation() - Camera->GetForwardVector() * 300);

        GGFDefaultCharacter->GetMesh()->SetOwnerNoSee(false);
        GGFDefaultCharacter->GetFirstPersonArms()->SetOwnerNoSee(true);
        GGFDefaultCharacter->GetFirstPersonLegs()->SetOwnerNoSee(true);
    }
}

void UGGFCSA_Dead::OnExit_Implementation()
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

    /* GGFDefaultCharacter 캐릭터 전용 부활 설정 */
    if(const AGGFDefaultCharacter* GGFDefaultCharacter = Cast<AGGFDefaultCharacter>(AvatarCharacter))
    {
        UCameraComponent* Camera = GGFDefaultCharacter->GetGameViewCamera();
        Camera->SetRelativeLocation(Camera->GetRelativeLocation() + Camera->GetForwardVector() * 300);

        GGFDefaultCharacter->GetMesh()->SetOwnerNoSee(true);
        GGFDefaultCharacter->GetFirstPersonArms()->SetOwnerNoSee(false);
        GGFDefaultCharacter->GetFirstPersonLegs()->SetOwnerNoSee(false);
    }
}
