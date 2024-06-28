// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GGFGA_SpawnTurret.h"

#include "GameFramework/Character.h"

void UGGFGA_SpawnTurret::SpawnActor()
{
    // 유효성 검사
    if(ActorToSpawn == nullptr) return;

    // 서버에서만 스폰 가능
    if(!HasAuthority(&CurrentActivationInfo)) return;

    // 중복 호출 방지
    if(bActorSpawned) return;
    bActorSpawned = true;

    if(auto World = GetWorld())
    {
        // 기존에 스폰된 액터 파괴
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
        FVector SpawnLocation = GetAvatarCharacter()->GetMesh()->GetSocketLocation(HandSocketName);
        FRotator SpawnRotation = ActorTransform.GetRotation().Rotator();

        // 에너지 실드 스폰
        SpawnedActor = World->SpawnActor(ActorToSpawn, &SpawnLocation, &SpawnRotation, ActorSpawnParameters);
        SpawnedActor->SetLifeSpan(SpawnedActorLifeTime);
    }
}
