// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFGA_SpawnActor.h"

void UGGFGA_SpawnActor::PreActivate(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
    Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);

    bActorSpawned = false;
}

void UGGFGA_SpawnActor::OnPlayMontageNotifyBegin_Implementation(FName NotifyName)
{
    Super::OnPlayMontageNotifyBegin_Implementation(NotifyName);

    if(NotifyName == SpawnNotifyName)
    {
        SpawnEnergyShield();
    }
}

void UGGFGA_SpawnActor::OnMontageCompleted_Implementation()
{
    Super::OnMontageCompleted_Implementation();

    SpawnEnergyShield();
}

void UGGFGA_SpawnActor::SpawnEnergyShield()
{
    // 서버에서만 스폰 가능
    if(!HasAuthority(&CurrentActivationInfo)) return;

    // 중복 호출 방지
    if(bActorSpawned) return;
    bActorSpawned = true;

    if(auto World = GetWorld())
    {
        // 기존에 설치된 에너지 실드 파괴
        if(SpawnedActor.IsValid())
        {
            SpawnedActor->Destroy();
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
        SpawnedActor = World->SpawnActor(ActorToSpawn, &SpawnLocation, &SpawnRotation, ActorSpawnParameters);
        SpawnedActor->SetLifeSpan(SpawnedActorLifeTime);
    }
}
