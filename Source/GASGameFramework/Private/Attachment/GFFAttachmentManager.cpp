// Fill out your copyright notice in the Description page of Project Settings.


#include "Attachment/GFFAttachmentManager.h"

#include "Attachment/GFFAttachmentDefinition.h"
#include "Attachment/GFFAttachmentSlotInterface.h"

UGFFAttachmentManager::UGFFAttachmentManager()
{
    bWantsInitializeComponent = true;
}

void UGFFAttachmentManager::InitializeComponent()
{
    Super::InitializeComponent();

    if(AActor* Owner = GetOwner())
    {
        const TArray<UActorComponent*> Components = Owner->GetComponentsByInterface(UGFFAttachmentSlotInterface::StaticClass());
        Slots.Reserve(Components.Num());
        for (UActorComponent* Component : Components)
        {
            Slots.Emplace(IGFFAttachmentSlotInterface::Execute_GetSlotTag(Component), Component);
        }
    }
}

void UGFFAttachmentManager::SetTargetMesh(UMeshComponent* InTargetMesh)
{
    // null 검사
    if(InTargetMesh == nullptr) return;

    // TargetMesh 설정
    TargetMesh = InTargetMesh;

    // 사용 가능한 슬롯 가져오기
    GetSlots();

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
    const TObjectPtr<UActorComponent> Component = Slots[SlotTag];
    if(Component->IsA(UStaticMeshComponent::StaticClass()))
        IGFFAttachmentSlotInterface::Execute_SetMesh(Component, Attachment->GetStaticMesh());
    else if(Component->IsA(USkeletalMeshComponent::StaticClass()))
        IGFFAttachmentSlotInterface::Execute_SetMesh(Component, Attachment->GetSkeletalMesh());

    // TODO 총기 스탯 혹은 스펙 옵션 설정
}

void UGFFAttachmentManager::GetSlots()
{
    if(const AActor* Owner = GetOwner())
    {
        const TArray<UActorComponent*> Components = Owner->GetComponentsByInterface(UGFFAttachmentSlotInterface::StaticClass());
        Slots.Reserve(Components.Num());
        for (UActorComponent* Component : Components)
        {
            Slots.Emplace(IGFFAttachmentSlotInterface::Execute_GetSlotTag(Component), Component);
        }
    }
}
