// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFHealthWidget.h"
#include "GGFHealthBar.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * 체력 및 실드를 하나의 프로그레스 바로 표시하기 위한 위젯 클래스
 */
UCLASS()
class GGFWIDGETSYSTEM_API UGGFHealthBar : public UGGFHealthWidget
{
    GENERATED_BODY()

protected:
    /* 컴포넌트 */

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Health")
    TObjectPtr<UProgressBar> HealthBar;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "Health")
    TObjectPtr<UTextBlock> HealthValueText;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "Health")
    TObjectPtr<UTextBlock> MaxHealthValueText;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "Health")
    TObjectPtr<UTextBlock> HealthRegenRateValueText;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Shield")
    TObjectPtr<UProgressBar> ShieldBar;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "Shield")
    TObjectPtr<UTextBlock> ShieldValueText;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float InterpSpeed = 20;

protected:
    /* UserWidget */

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    /* AttributesWidget */

    virtual void OnAttributeValueChange_Implementation(float OldAttributeValue) override;
    virtual void OnMaxAttributeValueChange_Implementation(float OldMaxAttributeValue) override;
    virtual void OnAttributeRegenRateValueChange_Implementation(float OldAttributeRegenRateValue) override;
    virtual void OnShieldAttributeValueChange_Implementation(float OldAttributeValue) override;

    /* 메서드 */

    virtual void RefreshAttributeBar(float InDeltaTime);
};
