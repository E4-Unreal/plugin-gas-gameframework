// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GGFActorWidget.h"
#include "GGFAttributesWidget.generated.h"

/* 헤더 매크로 */

// Attribute Setter 선언
#define DECLARE_ATTRIBUTE_SETTER(AttributeName) virtual void Set##AttributeName(float Value){ };

// AttributeValueChange 이벤트 선언
#define DECLARE_ATTRIBUTE_VALUE_CHANGE_HANDLE(AttributeName) \
    FDelegateHandle On##AttributeName##AttributeValueChangeHandle; \
    void On##AttributeName##AttributeValueChanged(const FOnAttributeChangeData& Data) \
    { \
        Set##AttributeName(Data.NewValue); \
    }

/* CPP 매크로 */

// GetAttributeValues에서 사용
#define REFRESH_ATTRIBUTE_VALUE(AttributeClass, AttributeName) \
    { \
        bool bFound; \
        float AttributeValue = TargetSystem->GetGameplayAttributeValue(AttributeClass::Get##AttributeName##Attribute(), bFound);   \
        if(bFound) Set##AttributeName(AttributeValue); \
    }

// Attribute Value Change 이벤트 바인딩
#define BIND_ATTRIBUTE_VALUE_CHANGE_EVENT(ClassName, AttributeName)  \
    TargetSystem->GetGameplayAttributeValueChangeDelegate(ClassName::Get##AttributeName##Attribute())   \
    .AddUObject(this, &ThisClass::On##AttributeName##AttributeValueChanged);

// Attribute Value Change 이벤트 언바인딩
#define UNBIND_ATTRIBUTE_VALUE_CHANGE_EVENT(ClassName, AttributeName)  \
    TargetSystem->GetGameplayAttributeValueChangeDelegate(ClassName::Get##AttributeName##Attribute())   \
    .Remove(On##AttributeName##AttributeValueChangeHandle);

class UAbilitySystemComponent;

/**
 * Attribute 전용 위젯 클래스
 */
UCLASS()
class GGFWIDGETSYSTEM_API UGGFAttributesWidget : public UGGFActorWidget
{
    GENERATED_BODY()

protected:
    TWeakObjectPtr<UAbilitySystemComponent> TargetSystem;

public:
    /* Attribute */

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGameplayAttribute Attribute;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    float AttributeValue;

    FDelegateHandle OnAttributeValueChangeHandle;

    /* MaxAttribute */

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGameplayAttribute MaxAttribute;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    float MaxAttributeValue;

    FDelegateHandle OnMaxAttributeValueChangeHandle;

    /* AttributeRegenRate */

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGameplayAttribute AttributeRegenRate;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    float AttributeRegenRateValue;

    FDelegateHandle OnAttributeRegenRateValueChangeHandle;

public:
    /* GGFActorWidget */

    virtual void SetActor(AActor* NewActor) override;

protected:
    /* 이벤트 */

    void OnAttributeChange(const FOnAttributeChangeData& Data);
    void OnMaxAttributeChange(const FOnAttributeChangeData& Data);
    void OnAttributeRegenRateChange(const FOnAttributeChangeData& Data);

    UFUNCTION(BlueprintNativeEvent)
    void OnAttributeValueChange(float OldAttributeValue);

    UFUNCTION(BlueprintNativeEvent)
    void OnMaxAttributeValueChange(float OldMaxAttributeValue);

    UFUNCTION(BlueprintNativeEvent)
    void OnAttributeRegenRateValueChange(float OldAttributeRegenRateValue);

    /* 메서드 */

    // 초기화를 위해 현재 Attribute 값을 가져옵니다.
    virtual void RefreshAttributeValues();

    // 이벤트 핸들링 메서드를 바인딩합니다.
    virtual void BindAttributeValueChangeEvents();

    // 이벤트 핸들링 메서드를 언바인딩합니다.
    virtual void UnBindAttributeValueChangeEvents();
};
