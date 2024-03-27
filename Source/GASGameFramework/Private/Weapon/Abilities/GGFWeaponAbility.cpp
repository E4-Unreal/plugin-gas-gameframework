// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Abilities/GGFWeaponAbility.h"

#include "Net/UnrealNetwork.h"

UGGFWeaponAbility::UGGFWeaponAbility()
{
    // 무기 어빌리티는 무기에 대한 레퍼런스가 필요하기 때문에 리플리케이트된 어빌리티 인스턴스를 사용합니다.
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
}

void UGGFWeaponAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Weapon)
}

void UGGFWeaponAbility::SetWeapon_Implementation(AActor* InWeapon)
{
    // 서버 전용
    const FGameplayAbilityActivationInfo& ActivationInfo = GetCurrentActivationInfo();
    if(!HasAuthority(&ActivationInfo)) return;

    // 중복 호출 방지
    if(Weapon.IsValid()) return;

    // 무기 레퍼런스 저장
    Weapon = InWeapon;

    // 서버에서는 호출되지 않기 때문에 수동으로 호출
    OnRep_Weapon();
}
