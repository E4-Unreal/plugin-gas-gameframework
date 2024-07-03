// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFTriggerBox.h"

#include "Components/BoxComponent.h"

AGGFTriggerBox::AGGFTriggerBox(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UBoxComponent>(CollisionComponentName))
{
    if(GetBoxCollision())
    {
        GetBoxCollision()->InitBoxExtent(FVector(100, 100, 100));
    }
}

void AGGFTriggerBox::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // TriggerBoxPivot 설정에 따라 BoxCollision 위치 조정
    SetBoxCollisionPosition();
}

void AGGFTriggerBox::SetBoxCollisionPosition()
{
    auto BoxCollision = GetBoxCollision();
    if(BoxCollision == nullptr) return;

    const FVector ScaledBoxExtent = BoxCollision->GetScaledBoxExtent();

    switch (TriggerBoxPivot)
    {
    case EGGFPivot::Center:
        BoxCollision->SetRelativeLocation(FVector(0, 0, 0));
        break;
    case EGGFPivot::Bottom:
        BoxCollision->SetRelativeLocation(FVector(0, 0, ScaledBoxExtent.Z));
        break;
    case EGGFPivot::Top:
        BoxCollision->SetRelativeLocation(FVector(0, 0, -ScaledBoxExtent.Z));
        break;
    case EGGFPivot::Custom:
        // 아무 행동도 하지 않습니다.
        break;
    }
}
