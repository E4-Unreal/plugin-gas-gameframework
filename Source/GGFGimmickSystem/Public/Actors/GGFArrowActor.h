// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGFArrowActor.generated.h"

class UArrowComponent;

/**
 * 레벨 디자인 시 위치와 방향을 표시하기 위해 화살표 컴포넌트가 포함된 기본 액터입니다.
 */
UCLASS()
class GGFGIMMICKSYSTEM_API AGGFArrowActor : public AActor
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetArrowComponent, Category = "Component")
    TObjectPtr<UArrowComponent> ArrowComponent;

public:
    AGGFArrowActor();

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UArrowComponent* GetArrowComponent() const { return ArrowComponent; }
};
