// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFAttributesWidget.h"
#include "GGFAttributesBar.generated.h"

class UTextBlock;
class UProgressBar;

/**
 * 프로그레스 바 형식의 어트리뷰트 전용 위젯 클래스입니다.
 */
UCLASS()
class GGFWIDGETSYSTEM_API UGGFAttributesBar : public UGGFAttributesWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UProgressBar> AttributeBar;

    UPROPERTY(meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> AttributeValueText;

    UPROPERTY(meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> MaxAttributeValueText;

    UPROPERTY(meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> AttributeRegenRateValueText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float InterpSpeed = 20;

protected:
    /* UserWidget */

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    /* AttributesWidget */

    virtual void OnAttributeValueChange_Implementation(float OldAttributeValue) override;
    virtual void OnMaxAttributeValueChange_Implementation(float OldMaxAttributeValue) override;
    virtual void OnAttributeRegenRateValueChange_Implementation(float OldAttributeRegenRateValue) override;

    /* 메서드 */

    virtual void RefreshAttributeBar(float InDeltaTime);
};
