// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFGA_SpawnProjectile.h"

#include "Animation/SkeletalMeshActor.h"
#include "Characters/GGFThirdPersonCharacter_Retarget.h"
#include "GameFramework/Character.h"
#include "Interfaces/GGFEquipmentManagerInterface.h"

void UGGFGA_SpawnProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    HideSelectedWeapon(true);
    SpawnSpecialWeapon();
}

void UGGFGA_SpawnProjectile::EndAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility, bool bWasCancelled)
{
    if(SpawnedSpecialWeapon)
    {
        SpawnedSpecialWeapon->Destroy();
        SpawnedSpecialWeapon = nullptr;
    }

    HideSelectedWeapon(false);

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGGFGA_SpawnProjectile::SpawnSpecialWeapon()
{
    if(!HasAuthority(&CurrentActivationInfo)) return;

    auto RetargetCharacter = Cast<AGGFThirdPersonCharacter_Retarget>(GetAvatarCharacter());
    USkeletalMeshComponent* CharacterMesh = RetargetCharacter ? RetargetCharacter->GetRetargetMesh() : GetAvatarCharacter()->GetMesh();

    if(!CharacterMesh->DoesSocketExist(WeaponSocketName)) return;

    if(auto World = GetWorld())
    {
        SpawnedSpecialWeapon = World->SpawnActor<ASkeletalMeshActor>(ASkeletalMeshActor::StaticClass());
        SpawnedSpecialWeapon->SetReplicates(true);
        SpawnedSpecialWeapon->GetSkeletalMeshComponent()->SetSkeletalMesh(SpecialWeaponMesh);

        FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
        SpawnedSpecialWeapon->AttachToComponent(CharacterMesh, AttachmentTransformRules, WeaponSocketName);
    }
}

void UGGFGA_SpawnProjectile::HideSelectedWeapon(bool bHide)
{
    if(bHide)
    {
        if(auto EquipmentManager = GetAvatarCharacter()->GetComponentsByInterface(UGGFEquipmentManagerInterface::StaticClass()).Last())
        {
            SelectedWeapon = IGGFEquipmentManagerInterface::Execute_GetSelectedEquipment(EquipmentManager);
            if(SelectedWeapon.IsValid())
            {
                SelectedWeapon->SetActorHiddenInGame(true);
            }
        }
    }
    else if(SelectedWeapon.IsValid())
    {
        SelectedWeapon->SetActorHiddenInGame(false);
    }
}

void UGGFGA_SpawnProjectile::SpawnActor()
{
    // 서버에서만 스폰 가능
    if(!HasAuthority(&CurrentActivationInfo)) return;

    // 중복 호출 방지
    if(bActorSpawned) return;
    bActorSpawned = true;

    // 유효성 검사
    if(ActorToSpawn && SpawnedSpecialWeapon)
    {
        FVector SpawnLocation;
        FRotator SpawnRotation;

        if(SpawnedSpecialWeapon->GetSkeletalMeshComponent()->DoesSocketExist(MuzzleSocketName))
        {
            FTransform MuzzleTransform = SpawnedSpecialWeapon->GetSkeletalMeshComponent()->GetSocketTransform(MuzzleSocketName);
            SpawnLocation = MuzzleTransform.GetLocation();
            SpawnRotation = MuzzleTransform.GetRotation().Rotator();
        }
        else
        {
            SpawnLocation = SpawnedSpecialWeapon->GetActorLocation();
            SpawnRotation = SpawnedSpecialWeapon->GetActorRotation();
        }

        if(GetAvatarCharacter()->Implements<UGGFAimingInterface>())
        {
            FVector TargetLocation = IGGFAimingInterface::Execute_GetTargetLocation(GetAvatarCharacter());
            FVector Direction = TargetLocation - SpawnLocation;
            SpawnRotation = Direction.Rotation();
        }

        if(auto World = GetWorld())
        {
            FActorSpawnParameters ActorSpawnParameters;
            ActorSpawnParameters.Owner = SpawnedSpecialWeapon;
            ActorSpawnParameters.Instigator = GetAvatarCharacter();
            World->SpawnActor(ActorToSpawn, &SpawnLocation, &SpawnRotation, ActorSpawnParameters);
        }
    }
}
