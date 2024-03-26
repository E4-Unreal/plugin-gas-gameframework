// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Components/GGFEquipmentManagerBase.h"

#include "Equipment/GGFEquipment.h"

UGGFEquipmentManagerBase::UGGFEquipmentManagerBase()
{
    bWantsInitializeComponent = true;
    SetIsReplicatedByDefault(true);
}

void UGGFEquipmentManagerBase::InjectDependencies(USkeletalMeshComponent* InSkeletalMesh)
{
    // null 검사
    if(InSkeletalMesh == nullptr) return;

    // 초기화는 한 번만 진행됩니다.
    if(bInitialized) return;
    bInitialized = true;

    // 스켈레탈 메시 할당
    SkeletalMesh = InSkeletalMesh;
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
    if(Equipment == nullptr || SkeletalMesh == nullptr || SocketName == NAME_None) return false;

    // 소켓 존재 여부 검사
    if(SkeletalMesh->GetSocketByName(SocketName) == nullptr) return false;

    // 액터를 스켈레탈 메시 소켓에 부착
    Equipment->AttachToComponent(SkeletalMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketName);

    return true;
}

const FGameplayTag UGGFEquipmentManagerBase::GetEquipmentSlot(TSubclassOf<AActor> EquipmentClass)
{
    // 유효성 검사
    if(EquipmentClass == nullptr || !EquipmentClass->ClassDefaultObject->Implements<UGGFEquipmentInterface>()) return FGameplayTag::EmptyTag;

    // 장비 슬롯 태그 반환
    return IGGFEquipmentInterface::Execute_GetEquipmentSlot(EquipmentClass->ClassDefaultObject);
}
