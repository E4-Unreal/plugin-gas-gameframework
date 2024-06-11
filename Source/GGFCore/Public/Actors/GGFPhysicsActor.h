// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "GGFPhysicsActor.generated.h"

/**
 * 멀티플레이 피직스 시뮬레이트 전용 스태틱 메시 액터입니다.
 */
UCLASS()
class GGFCORE_API AGGFPhysicsActor : public AStaticMeshActor
{
    GENERATED_BODY()

public:
    AGGFPhysicsActor();
};
