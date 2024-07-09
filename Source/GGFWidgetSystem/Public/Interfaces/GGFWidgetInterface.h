// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFWidgetInterface.generated.h"

UINTERFACE(Blueprintable)
class GGFWIDGETSYSTEM_API UGGFWidgetInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 위젯 전용 인터페이스
 */
class GGFWIDGETSYSTEM_API IGGFWidgetInterface
{
    GENERATED_BODY()

public:
    // 위젯 갱신
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Refresh();
};
