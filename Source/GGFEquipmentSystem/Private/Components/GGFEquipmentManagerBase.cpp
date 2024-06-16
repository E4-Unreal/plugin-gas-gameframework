// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GGFEquipmentManagerBase.h"

#include "GGFEquipment.h"
#include "GameFramework/Character.h"

UGGFEquipmentManagerBase::UGGFEquipmentManagerBase()
{
    bWantsInitializeComponent = true;
    SetIsReplicatedByDefault(true);
}

void UGGFEquipmentManagerBase::InitializeComponent()
{
    Super::InitializeComponent();

    // Owner가 캐릭터인 경우 기본 메시 자동 할당
    if(ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
    {
        SetTargetMesh(OwnerCharacter->GetMesh());
    }
}

void UGGFEquipmentManagerBase::SetTargetMesh(USkeletalMeshComponent* NewTargetMesh)
{
    // 중복 호출 방지
    if(TargetMesh == NewTargetMesh) return;

    // 스켈레탈 메시 할당
    TargetMesh = NewTargetMesh;

    // 스켈레탈 메시 업데이트
    OnTargetMeshChanged();

#if WITH_EDITOR
    // 유효성 검사
    bValid = TargetMesh.IsValid();
#endif
}

void UGGFEquipmentManagerBase::OnTargetMeshChanged()
{
    // TODO 기존 메시에 부착된 장비들을 새로운 메시에 부착
}

AActor* UGGFEquipmentManagerBase::SpawnEquipment(TSubclassOf<AActor> EquipmentClass)
{
    // 월드 가져오기
    UWorld* World = GetOwner()->GetWorld();

    // null 검사
    if(World == nullptr || EquipmentClass == nullptr) return nullptr;

    // Owner 및 Instigator 설정
    FActorSpawnParameters ActorSpawnParameters;
    ActorSpawnParameters.Owner = GetOwner();
    ActorSpawnParameters.Instigator = GetOwner()->GetInstigator();

    // Owner 위치에 액터 스폰
    const FVector SpawnLocation = GetOwner()->GetActorLocation();
    AActor* SpawnedActor = World->SpawnActor<AActor>(EquipmentClass, SpawnLocation, FRotator::ZeroRotator, ActorSpawnParameters);

    return SpawnedActor;
}

bool UGGFEquipmentManagerBase::AttachEquipment(AActor* Equipment, FName SocketName)
{
    // 유효성 검사
    if(Equipment == nullptr || TargetMesh == nullptr || SocketName == NAME_None) return false;

    // 소켓 존재 여부 검사
    if(TargetMesh->GetSocketByName(SocketName) == nullptr) return false;

    // 액터를 스켈레탈 메시 소켓에 부착
    Equipment->AttachToComponent(TargetMesh.Get(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketName);

    return true;
}
