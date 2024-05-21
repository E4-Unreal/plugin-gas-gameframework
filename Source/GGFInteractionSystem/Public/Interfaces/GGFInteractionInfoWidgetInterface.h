// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFInteractionInfoWidgetInterface.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class GGFINTERACTIONSYSTEM_API UGGFInteractionInfoWidgetInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 상호작용 오브젝트 정보 표시를 위한 위젯 클래스에서 구현
 */
class GGFINTERACTIONSYSTEM_API IGGFInteractionInfoWidgetInterface
{
    GENERATED_BODY()

public:
    // UI에 표시할 오브젝트 이름 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetDisplayName(const FText& NewDisplayName);

    // UI에 표시할 상호작용에 대한 설명 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetInteractionInfo(const FText& NewInteractionInfo);
};
