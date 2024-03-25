// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GGFAttributeSetBase.generated.h"

/* 헤더 파일에서 사용 */

// Attribute 정의 시 사용하는 매크로
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GGFTTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GGFTTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/* GetLifetimeReplicatedProps에서 사용 */

// Attribute 리플리케이트 등록을 위한 DOREPLIFETIME_CONDITION_NOTIFY 매크로 사용을 단순화하였습니다.
#define GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY(Attribute) DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Attribute, COND_None, REPNOTIFY_Always);

// Attribute, MaxAttribute 이름 규칙을 지닌 Attribute 그룹의 리플리케이트 등록을 위한 매크로입니다.
#define GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX(Attribute) \
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY(Attribute); \
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY(Max##Attribute);

// Attribute, MaxAttribute, AttributeRegenRate 이름 규칙을 지닌 Attribute 그룹의 리플리케이트 등록을 위한 매크로입니다.
#define GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX_AND_REGGFNRATE(Attribute) \
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX(Attribute) \
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY(Attribute##RegenRate);

/* LooseGameplayTag 추가 시 사용 */

// PostAttributeChange에서 사용
#define ADD_LOOSE_GAMEPLAYTAG_CONDITION_WITH_ATTRIBUTE(AttributeName, Expr, Tag) \
    if(Attribute == Get##AttributeName##Attribute())   \
    {   \
        if(Expr) \
        {   \
            GetOwningAbilitySystemComponent()->AddLooseGameplayTag(Tag);    \
        }   \
        return; \
    }

// OnRep_Attribute에서 사용
#define ADD_LOOSE_GAMEPLAYTAG_CONDITION(Expr, Tag) \
    if(Expr) \
    {   \
        GetOwningAbilitySystemComponent()->AddLooseGameplayTag(Tag);    \
    }

/* OnRep_Attribute에서 사용 */

// GAMEPLAYATTRIBUTE_REPNOTIFY 매크로 사용을 단순화하였습니다.
#define GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(Attribute) GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Attribute, Old##Attribute);

/* ClampAttributes에서 사용 */

// 0 <= Attribute <= MaxAttribute
#define CLAMP_ATTRIBUTE_WITH_ZERO_AND_MAX_ATTRIBUTE(Attribute, NewValue, AttributeName) \
    if(Attribute == Get##AttributeName##Attribute())  \
    {   \
        NewValue = FMath::Clamp(NewValue, 0.f, GetMax##AttributeName());   \
        return; \
    }

// 0 <= MaxAttribute
#define CLAMP_MAX_ATTRIBUTE_WITH_ZERO(Attribute, NewValue, AttributeName) \
    if(Attribute == GetMax##AttributeName##Attribute())  \
    {   \
        NewValue = FMath::Max(NewValue, 0.f);   \
        return; \
    }

// 0 <= Attribute <= MaxAttribute, 0 <= MaxAttribute
#define CLAMP_ATTRIBUTE_AND_MAX_ATTRIBUTE(Attribute, NewValue, AttributeName)   \
    if(Attribute == Get##AttributeName##Attribute()) \
    {   \
        NewValue = FMath::Clamp(NewValue, 0.f, GetMax##AttributeName());   \
        return; \
    }   \
    else if(Attribute == GetMax##AttributeName##Attribute())  \
    {   \
        NewValue = FMath::Max(NewValue, 0.f);   \
        return; \
    }

/* AdjustAttributes에서 사용 */

// MaxAttribute 값 변경 시 Attribute / MaxAttribute 비율을 유지하기 위해 Attribute 값 변경
#define ADJUST_ATTRIBUTE_FOR_MAX_ATTRIBUTE_CHANGGF(AttributeName)    \
    if(Attribute == GetMax##AttributeName##Attribute())   \
    {   \
        AdjustAttributeForMaxChange(AttributeName, Max##AttributeName, OldValue, NewValue, Get##AttributeName##Attribute());   \
        return; \
    }

/**
 * AttributeSet 클래스에서 공용으로 사용할 헬퍼 매크로 및 함수를 포함하고 있습니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGGFAttributeSetBase : public UAttributeSet
{
    GENERATED_BODY()

public:
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

protected:
    /*
     * MaxAttribute 값 변경 시 기존 Attribute / MaxAttribute 비율이 유지되도록 관련 Attribute 값을 변경합니다.
     * ex) 최대 체력 값이 변경되면 기존 체력 비율이 유지되도록 체력 값 역시 변경됩니다. (60/100 > 90/150)
     * 이 기능을 사용하는 경우 Attribute 초기화 시 MaxAttribute 값만 수정해도 자동으로 Attribute = MaxAttribute 로 설정됩니다.
     */
    void AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, const float OldMaxValue, const float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) const;

    // Attribute의 Base 혹은 Current 값을 Clamp 합니다.
    virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const;

    // MaxAttribute 값 변경 시 Attribute / MaxAttribute 의 비율을 유지합니다.
    virtual void AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue);
};
