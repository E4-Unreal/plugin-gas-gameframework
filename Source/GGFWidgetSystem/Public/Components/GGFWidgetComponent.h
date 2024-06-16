// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GGFWidgetComponent.generated.h"

/**
 * GASGameFramework 플러그인에서 범용적으로 사용할 위젯 컴포넌트 클래스
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFWIDGETSYSTEM_API UGGFWidgetComponent : public UWidgetComponent
{
    GENERATED_BODY()

public:
    /* WidgetComponent */

    virtual void SetWidget(UUserWidget* InWidget) override;
};
