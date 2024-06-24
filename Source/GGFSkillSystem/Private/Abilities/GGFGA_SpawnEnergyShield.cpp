// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFGA_SpawnEnergyShield.h"

#include "Actors/GGFEnergyShield.h"

UGGFGA_SpawnEnergyShield::UGGFGA_SpawnEnergyShield()
{
    /* 기본 에셋 설정 */
    EnergyShieldClass = AGGFEnergyShield::StaticClass();
}

void UGGFGA_SpawnEnergyShield::PreActivate(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
    Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);

    bEnergyShieldSpawned = false;
}

void UGGFGA_SpawnEnergyShield::OnPlayMontageNotifyBegin_Implementation(FName NotifyName)
{
    Super::OnPlayMontageNotifyBegin_Implementation(NotifyName);

    if(NotifyName == SpawnNotifyName)
    {
        SpawnEnergyShield();
    }
}

void UGGFGA_SpawnEnergyShield::OnMontageCompleted_Implementation()
{
    Super::OnMontageCompleted_Implementation();

    SpawnEnergyShield();
}

void UGGFGA_SpawnEnergyShield::SpawnEnergyShield()
{
    // 서버에서만 스폰 가능
    if(!HasAuthority(&CurrentActivationInfo)) return;

    // 중복 호출 방지
    if(bEnergyShieldSpawned) return;
    bEnergyShieldSpawned = true;

    if(auto World = GetWorld())
    {
        // 기존에 설치된 에너지 실드 파괴
        if(SpawnedEnergyShield.IsValid())
        {
            SpawnedEnergyShield->Destroy();
        }

        // 스폰 매개 변수 설정
        auto AvatarActor = GetAvatarActorFromActorInfo();
        FActorSpawnParameters ActorSpawnParameters;
        ActorSpawnParameters.Owner = AvatarActor;
        ActorSpawnParameters.Instigator = AvatarActor->GetInstigator();

        // 스폰 위치 설정
        const FTransform& ActorTransform = AvatarActor->GetActorTransform();
        FVector SpawnLocation = ActorTransform.GetLocation();
        FRotator SpawnRotation = ActorTransform.GetRotation().Rotator();

        // 에너지 실드 스폰
        SpawnedEnergyShield = World->SpawnActor(EnergyShieldClass, &SpawnLocation, &SpawnRotation, ActorSpawnParameters);
        SpawnedEnergyShield->SetLifeSpan(EnergyShieldLifeTime);
    }
}
