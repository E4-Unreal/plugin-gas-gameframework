// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFEquipment.h"

#include "GGFEquipmentGameplayTags.h"

AGGFEquipment::AGGFEquipment()
{
    /* 초기화 */

    // 리플리케이트 설정
    SetReplicates(true);

    // 기본값 설정
    using namespace GGFGameplayTags::Equipment;
    EquipmentType = Root;
    EquipmentSlot = Slot::Root;
}

void AGGFEquipment::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);

    // 서버 로직
    CheckOwner();
}

void AGGFEquipment::OnRep_Owner()
{
    Super::OnRep_Owner();

    // 클라이언트 로직
    CheckOwner();
}

void AGGFEquipment::CheckOwner()
{
    if(GetOwner() == nullptr)
        OnUnEquip();
    else
        OnEquip();
}

void AGGFEquipment::Equip_Implementation(AActor* NewOwner)
{
    SetOwner(NewOwner);
}

void AGGFEquipment::UnEquip_Implementation()
{
    SetOwner(nullptr);
}

void AGGFEquipment::Activate_Implementation()
{
    // TODO 장비 기능 활성화 (선택 사항)
}

void AGGFEquipment::Deactivate_Implementation()
{
    // TODO 장비 기능 비활성화 (선택 사항)
}

void AGGFEquipment::OnEquip_Implementation()
{
    // TODO 장비 장착 애니메이션, 장비 스탯 적용 등
}

void AGGFEquipment::OnUnEquip_Implementation()
{
    // TODO 장비 스탯 적용 해제 등
}
