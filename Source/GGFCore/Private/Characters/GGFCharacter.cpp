// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GGFCharacter.h"

#include "AbilitySystem/GGFDamageableAbilitySystem.h"
#include "Components/GGFGameplayEventManager.h"
#include "Components/GGFPawnStateMachine.h"

FName AGGFCharacter::AbilitySystemName(TEXT("AbilitySystem"));
FName AGGFCharacter::GameplayEventManagerName(TEXT("GameplayEventManager"));
FName AGGFCharacter::GameplayStateMachineName(TEXT("GameplayStateMachine"));

AGGFCharacter::AGGFCharacter(const FObjectInitializer& ObjectInitializer)
{
    bReplicates = true;

    /* AbilitySystem */
    AbilitySystem = CreateDefaultSubobject<UGGFDamageableAbilitySystem>(AbilitySystemName);

    /* GameplayEventManager */
    GameplayEventManager = CreateDefaultSubobject<UGGFGameplayEventManager>(GameplayEventManagerName);

    /* GameplayStateMachine */
    GameplayStateMachine = CreateDefaultSubobject<UGGFPawnStateMachine>(GameplayStateMachineName);

    /* 초기화 */
    // GECharacter
    BoneNamesToHide.Emplace("weapon"); // 파라곤
    BoneNamesToHide.Emplace("pistol"); // 파라곤
    BoneNamesToHide.Emplace("weapon_r"); // 파라곤
}

void AGGFCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 이벤트 바인딩
    BindEvents();

    // BoneNamesToHide에 설정된 스켈레톤을 숨깁니다.
    HideBones();
}

void AGGFCharacter::BindEvents()
{
    if(HasAuthority())
    {
        OnServerBindEvents();
    }

    OnBindEvents();
}

void AGGFCharacter::OnBindEvents()
{
    // OnDead
    if(auto CastedAbilitySystem = Cast<UGGFDamageableAbilitySystem>(GetAbilitySystem()))
    {
        CastedAbilitySystem->OnDead.AddDynamic(this, &ThisClass::OnDead);
    }
}

void AGGFCharacter::OnServerBindEvents()
{
}

void AGGFCharacter::OnDead_Implementation()
{
    // TODO Destroy 등 죽음 처리
}

void AGGFCharacter::HideBones()
{
    USkeletalMeshComponent* CharacterMesh = GetMesh();
    for (FName BoneName : BoneNamesToHide)
    {
        CharacterMesh->HideBoneByName(BoneName, PBO_None);
    }
}
