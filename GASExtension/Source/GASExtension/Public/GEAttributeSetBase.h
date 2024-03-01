// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GEAttributeSetBase.generated.h"

// AttributeSet 헬퍼 매크로
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// GEAttributeSetBase 헬퍼 매크로
#define GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY(Attribute) DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Attribute, COND_None, REPNOTIFY_Always);

#define GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(Attribute) GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Attribute, Old##Attribute);

/**
 * AttributeSet 클래스에서 공용으로 사용할 헬퍼 매크로 및 함수를 포함하고 있습니다.
 */
UCLASS()
class GASEXTENSION_API UGEAttributeSetBase : public UAttributeSet
{
    GENERATED_BODY()

protected:
    /*
     * MaxAttribute 값 변경 시 기존 Attribute / MaxAttribute 비율이 유지되도록 관련 Attribute 값을 변경합니다.
     * ex) 최대 체력 값이 변경되면 기존 체력 비율이 유지되도록 체력 값 역시 변경됩니다. (60/100 > 90/150)
     * 이 기능을 사용하는 경우 Attribute 초기화 시 MaxAttribute 값만 수정해도 자동으로 Attribute = MaxAttribute 로 설정됩니다.
     */
    void AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, const float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) const;
};
