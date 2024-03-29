// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/GGFEquipment.h"

AGGFEquipment::AGGFEquipment()
{
    SetReplicates(true);
}

void AGGFEquipment::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);

    if(GetOwner() == nullptr)
        OnUnEquip();
    else
        OnEquip();
}

void AGGFEquipment::OnRep_Owner()
{
    Super::OnRep_Owner();

    if(GetOwner() == nullptr)
        OnUnEquip();
    else
        OnEquip();
}

void AGGFEquipment::OnEquip_Implementation()
{
}

void AGGFEquipment::OnUnEquip_Implementation()
{
}
