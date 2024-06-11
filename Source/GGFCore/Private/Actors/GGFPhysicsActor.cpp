// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFPhysicsActor.h"

AGGFPhysicsActor::AGGFPhysicsActor()
{
    /* 기본 설정 */
    bReplicates = true;
    SetReplicatingMovement(true);
    bStaticMeshReplicateMovement = true;
    GetStaticMeshComponent()->BodyInstance.bSimulatePhysics = true;
    GetStaticMeshComponent()->SetGenerateOverlapEvents(true);
    SetMobility(EComponentMobility::Movable);

    /* 기본 에셋 설정 */
    static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObjectFinder(TEXT("/LevelPrototyping/Meshes/SM_ChamferCube"));
    if(StaticMeshObjectFinder.Succeeded())
    {
        GetStaticMeshComponent()->SetStaticMesh(StaticMeshObjectFinder.Object);
    }
}
