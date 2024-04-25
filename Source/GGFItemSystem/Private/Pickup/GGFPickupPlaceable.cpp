// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup/GGFPickupPlaceable.h"

#include "GGFItemDataSubsystem.h"

void AGGFPickupPlaceable::BeginPlay()
{
    Super::BeginPlay();

    // 아이템 서브 시스템에서 아이템 ID 검색 후 초기화 진행
    if(UGGFItemDataSubsystem* ItemDataSubsystem = GetGameInstance()->GetSubsystem<UGGFItemDataSubsystem>())
    {
        InitFromItemDefinition(ItemDataSubsystem->GetOrCreateItemDefinition(ItemID));
    }
}
