// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFAttributesWidget.h"
#include "GGFHealthWidget.generated.h"

/**
 * 체력 어트리뷰트에 방어막에 어트리뷰트가 추가되었습니다.
 */
UCLASS()
class GGFWIDGETSYSTEM_API UGGFHealthWidget : public UGGFAttributesWidget
{
    GENERATED_BODY()

public:
    /* Shield */

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGameplayAttribute ShieldAttribute;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    float ShieldAttributeValue;

    FDelegateHandle OnShieldAttributeValueChangeHandle;

public:
    UGGFHealthWidget();

protected:
    /* AttributesWidget */

    virtual void RefreshAttributeValues() override;
    virtual void BindAttributeValueChangeEvents() override;
    virtual void UnBindAttributeValueChangeEvents() override;

    /* 이벤트 */

    void OnShieldAttributeChange(const FOnAttributeChangeData& Data);

    UFUNCTION(BlueprintNativeEvent)
    void OnShieldAttributeValueChange(float OldAttributeValue);
};
