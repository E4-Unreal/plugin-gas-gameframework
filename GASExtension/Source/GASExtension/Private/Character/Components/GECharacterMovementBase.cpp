// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Components/GECharacterMovementBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GEGameplayTags.h"

UGECharacterMovementBase::UGECharacterMovementBase()
{
    // 초기화
    bWantsInitializeComponent = true;

    // 캐릭터 무브먼트 설정
    NavAgentProps.bCanCrouch = true;
    bCanWalkOffLedgesWhenCrouching = true;

    // 태그 기본값 설정
    FallingTag = GEGameplayTags::State::FallingTag;
    CrouchingTag = GEGameplayTags::State::CrouchingTag;
}

void UGECharacterMovementBase::InitializeComponent()
{
    Super::InitializeComponent();

    OwnerAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(PawnOwner);
}

void UGECharacterMovementBase::SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode)
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

void UGECharacterMovementBase::Crouch(bool bClientSimulation)
{
    // Crouch 게임플레이 태그 부착
    if(OwnerAbilitySystem.IsValid())
    {
        OwnerAbilitySystem->AddLooseGameplayTag(CrouchingTag);
    }

    Super::Crouch(bClientSimulation);
}

void UGECharacterMovementBase::UnCrouch(bool bClientSimulation)
{
    // Crouch 게임플레이 태그 제거
    if(OwnerAbilitySystem.IsValid())
    {
        OwnerAbilitySystem->RemoveLooseGameplayTag(CrouchingTag);
    }

    Super::UnCrouch(bClientSimulation);
}
