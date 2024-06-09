// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGFSplineActor.generated.h"

class USplineComponent;

/**
 * 레벨 디자인 시 경로를 표시하기 위해 스플라인 컴포넌트가 포함된 기본 액터입니다.
 */
UCLASS(ComponentWrapperClass)
class GGFGIMMICKSYSTEM_API AGGFSplineActor : public AActor
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetSplineComponent, Category = "Component")
    TObjectPtr<USplineComponent> SplineComponent;

public:
    AGGFSplineActor();

    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USplineComponent* GetSplineComponent() const { return SplineComponent; }
};
