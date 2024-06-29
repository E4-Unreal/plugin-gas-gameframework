// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFDestructibleActor.h"

AGGFDestructibleActor::AGGFDestructibleActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* DisplayMesh */
    DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    SetRootComponent(DisplayMesh);

    /* 기본 에셋 설정 */
    ConstructorHelpers::FObjectFinder<UStaticMesh> DisplayMeshFinder(TEXT("/Engine/BasicShapes/Cube"));
    if(DisplayMeshFinder.Succeeded())
    {
        GetDisplayMesh()->SetStaticMesh(DisplayMeshFinder.Object);

        ConstructorHelpers::FObjectFinder<UMaterialInterface> DisplayMeshMaterialFinder(TEXT("/Engine/BasicShapes/BasicShapeMaterial"));
        if(DisplayMeshMaterialFinder.Succeeded()) GetDisplayMesh()->SetMaterial(0, DisplayMeshMaterialFinder.Object);
    }
}

void AGGFDestructibleActor::OnDead_Implementation()
{
    Super::OnDead_Implementation();

    Destroy();
}
