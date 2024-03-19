// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Equipment\GEEquipment.h"

AGEEquipment::AGEEquipment()
{
    SetReplicates(true);
}

void AGEEquipment::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);

    if(GetOwner() == nullptr)
        OnUnEquip();
    else
        OnEquip();
}

void AGEEquipment::OnRep_Owner()
{
    Super::OnRep_Owner();

    if(GetOwner() == nullptr)
        OnUnEquip();
    else
        OnEquip();
}

void AGEEquipment::OnEquip_Implementation()
{
}

void AGEEquipment::OnUnEquip_Implementation()
{
}
