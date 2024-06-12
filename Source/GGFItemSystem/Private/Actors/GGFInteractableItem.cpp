// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFInteractableItem.h"

#include "Components/GGFInteractableComponent.h"
#include "Components/GGFItemDataManager.h"
#include "Data/GGFItemDefinition.h"

AGGFInteractableItem::AGGFInteractableItem()
{
    /* Item Manager */
    ItemDataManager = CreateDefaultSubobject<UGGFItemDataManager>(TEXT("ItemDataManager"));
}

void AGGFInteractableItem::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    /* Item Manager */
    ItemDataManager->OnIDUpdated.AddDynamic(this, &ThisClass::OnIDUpdated);
}

void AGGFInteractableItem::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // 초기화
    OnIDUpdated(ItemDataManager->GetID());
}

void AGGFInteractableItem::OnIDUpdated(int32 NewID)
{
    // 아이템 데이터 설정
    const auto& ItemData = GetItemDataManager()->GetData();
    GetDisplayMesh()->SetStaticMesh(ItemData.DisplayMesh);
    GetInteractableComponent()->DisplayName = ItemData.DisplayName;
}
