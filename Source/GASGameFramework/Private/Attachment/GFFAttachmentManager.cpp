// Fill out your copyright notice in the Description page of Project Settings.


#include "Attachment/GFFAttachmentManager.h"

#include "Attachment/GFFAttachmentComponent.h"
#include "Attachment/GFFAttachmentDefinition.h"

UGFFAttachmentManager::UGFFAttachmentManager()
{
    StaticMeshComponentClass = UGFFAttachmentComponent::StaticClass();
}

void UGFFAttachmentManager::SetTargetMesh(UMeshComponent* InTargetMesh)
{
    // null 검사
    if(InTargetMesh == nullptr) return;

    // TargetMesh 설정
    TargetMesh = InTargetMesh;

    // 슬롯 생성
    CreateSlots();

    // 기본 부착물 부착
    for (UGFFAttachmentDefinition* Attachment : DefaultAttachments)
    {
        SetAttachment(Attachment);
    }
}

void UGFFAttachmentManager::SetAttachment(UGFFAttachmentDefinition* Attachment)
{
    // 유효성 검사
    if(!TargetMesh.IsValid() || Attachment == nullptr || !Attachment->IsValid()) return;

    // 슬롯 맵 확인
    const FGameplayTag& SlotTag = Attachment->GetSlot();
    if(!Slots.Contains(SlotTag)) return;

    // 메시 설정
    Slots[SlotTag]->SetStaticMesh(Attachment->GetAttachmentMesh());

    // TODO 총기 스탯 혹은 스펙 옵션 설정
}

void UGFFAttachmentManager::CreateSlots()
{
    // 유효성 검사
    if(!TargetMesh.IsValid()) return;

    // 중복 호출 검사
    if(!Slots.IsEmpty()) return;

    // 슬롯 생성
    Slots.Reserve(SlotMap.Num());
    for (const auto& [SlotTag, SocketName] : SlotMap)
    {
        if(SlotTag.IsValid() && SocketName.IsValid())
        {
            Slots.Add(SlotTag, AttachStaticMeshComponentToTarget(SocketName));
        }
    }
}

UStaticMeshComponent* UGFFAttachmentManager::AttachStaticMeshComponentToTarget(const FName& SocketName) const
{
    UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(TargetMesh->GetOwner(), StaticMeshComponentClass);
    StaticMeshComponent->CreationMethod = EComponentCreationMethod::Instance; // 에디터 표시
    StaticMeshComponent->RegisterComponent();
    TargetMesh->GetOwner()->AddOwnedComponent(StaticMeshComponent);
    StaticMeshComponent->AttachToComponent(TargetMesh.Get(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketName);

    return StaticMeshComponent;
}
