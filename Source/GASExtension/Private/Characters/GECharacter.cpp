// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GECharacter.h"

#include "GEGameplayTags.h"
#include "AbilitySystem/GEDamageableAbilitySystem.h"
#include "Components/GEGameplayEventManager.h"
#include "Components/GEGameplayStateMachine.h"

FName AGECharacter::AbilitySystemName(TEXT("AbilitySystem"));
FName AGECharacter::GameplayEventManagerName(TEXT("GameplayEventManager"));
FName AGECharacter::GameplayStateMachineName(TEXT("GameplayStateMachine"));

AGECharacter::AGECharacter(const FObjectInitializer& ObjectInitializer)
{
    bReplicates = true;
    
    /* AbilitySystem */
    AbilitySystem = CreateDefaultSubobject<UGEDamageableAbilitySystem>(AbilitySystemName);

    /* GameplayEventManager */
    GameplayEventManager = CreateDefaultSubobject<UGEGameplayEventManager>(GameplayEventManagerName);

    /* GameplayStateMachine */
    GameplayStateMachine = CreateDefaultSubobject<UGEGameplayStateMachine>(GameplayStateMachineName);

    /* 초기화 */
    // GECharacter
    BoneNamesToHide.Emplace("weapon"); // 파라곤
    BoneNamesToHide.Emplace("pistol"); // 파라곤
    BoneNamesToHide.Emplace("weapon_r"); // 파라곤
}

void AGECharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 이벤트 바인딩
    BindEvents();

    // BoneNamesToHide에 설정된 스켈레톤을 숨깁니다.
    HideBones();
}

void AGECharacter::BindEvents()
{
    if(HasAuthority())
    {
        OnServerBindEvents();
    }

    OnBindEvents();
}

void AGECharacter::OnBindEvents()
{
    // OnDead
    if(auto CastedAbilitySystem = Cast<UGEDamageableAbilitySystem>(GetAbilitySystem()))
    {
        CastedAbilitySystem->OnDead.AddDynamic(this, &ThisClass::OnDead);
    }
}

void AGECharacter::OnServerBindEvents()
{
}

void AGECharacter::OnDead_Implementation()
{
    // TODO Destroy 등 죽음 처리
}

void AGECharacter::HideBones()
{
    USkeletalMeshComponent* CharacterMesh = GetMesh();
    for (FName BoneName : BoneNamesToHide)
    {
        CharacterMesh->HideBoneByName(BoneName, PBO_None);
    }
}
