// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFInteractableItem.h"

#include "Components/GGFInteractableComponent.h"
#include "Components/GGFItemDataManager.h"
#include "Data/GGFItemDefinition.h"
#include "Net/UnrealNetwork.h"

AGGFInteractableItem::AGGFInteractableItem()
{
    /* Item Manager */
    ItemDataManager = CreateDefaultSubobject<UGGFItemDataManager>(TEXT("ItemDataManager"));
}

void AGGFInteractableItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Amount);
}

void AGGFInteractableItem::PreInitializeComponents()
{
    Super::PreInitializeComponents();

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
    SetAmount(ItemData.Amount);
}

void AGGFInteractableItem::UpdateDisplayName()
{
    const auto& ItemData = GetItemDataManager()->GetData();
    FString DisplayNameString = ItemData.DisplayName.ToString() + " (" + FString::FromInt(Amount) + ")";
    GetInteractableComponent()->DisplayName = FName(DisplayNameString);
    GetInteractableComponent()->RefreshWidget();
}

void AGGFInteractableItem::OnRep_Amount(int32 OldAmount)
{
    if(Amount == OldAmount) return;

    SetAmount(Amount);
}

void AGGFInteractableItem::SetAmount(int32 NewAmount)
{
    Amount = FMath::Max(0, NewAmount);

    if(Amount <= 0) Destroy();

    UpdateDisplayName();
}
