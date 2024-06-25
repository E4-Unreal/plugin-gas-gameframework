// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GGFGameplayEffect.generated.h"

/* 어트리뷰트 */

#define DEFINE_ATTRIBUTE_MODIFIER_PTR(AttributeName) \
    FGameplayModifierInfo* AttributeName##ModifierPtr; \
    FGameplayModifierInfo* Max##AttributeName##ModifierPtr; \
    FGameplayModifierInfo* AttributeName##RegenRateModifierPtr;

#define SET_ATTRIBUTE_MODIFIER(AttributeClass, AttributeName) \
    SetModifier(AttributeName##ModifierPtr, AttributeClass::Get##AttributeName##Attribute(), Data::Attribute::AttributeName, GET_MEMBER_NAME_CHECKED(AttributeClass, AttributeName)); \
    SetModifier(Max##AttributeName##ModifierPtr, AttributeClass::GetMax##AttributeName##Attribute(), Data::MaxAttribute::AttributeName, GET_MEMBER_NAME_CHECKED(AttributeClass, Max##AttributeName)); \
    SetModifier(AttributeName##RegenRateModifierPtr, AttributeClass::Get##AttributeName##RegenRateAttribute(), Data::AttributeRegenRate::AttributeName, GET_MEMBER_NAME_CHECKED(AttributeClass, AttributeName##RegenRate));

#define REMOVE_ATTRIBUTE_MODIFIER(AttributeName) \
    RemoveModifier(AttributeName##ModifierPtr); \
    RemoveModifier(Max##AttributeName##ModifierPtr); \
    RemoveModifier(AttributeName##RegenRateModifierPtr);

/* 스탯 */

#define DEFINE_STAT_MODIFIER_PTR(StatName) \
    FGameplayModifierInfo* StatName##ModifierPtr; \
    FGameplayModifierInfo* Max##StatName##ModifierPtr;

#define SET_STAT_MODIFIER(StatClass, StatName) \
    SetModifier(StatName##ModifierPtr, StatClass::Get##StatName##Attribute(), Data::Stat::StatName, GET_MEMBER_NAME_CHECKED(StatClass, StatName)); \
    SetModifier(Max##StatName##ModifierPtr, StatClass::GetMax##StatName##Attribute(), Data::MaxStat::StatName, GET_MEMBER_NAME_CHECKED(StatClass, Max##StatName));

#define REMOVE_STAT_MODIFIER(StatName) \
    RemoveModifier(StatName##ModifierPtr); \
    RemoveModifier(Max##StatName##ModifierPtr);

class UTargetTagsGameplayEffectComponent;
class UTargetTagRequirementsGameplayEffectComponent;

/**
 * GASGameFramework 플러그인 전용 게임플레이 이펙트 클래스
 */
UCLASS()
class GGFCORE_API UGGFGameplayEffect : public UGameplayEffect
{
    GENERATED_BODY()

    /* 컴포넌트 */

    TWeakObjectPtr<UTargetTagRequirementsGameplayEffectComponent> TargetTagRequirementsComponent;
    TWeakObjectPtr<UTargetTagsGameplayEffectComponent> TargetTagsGameplayEffectComponent;

public:
    UGGFGameplayEffect();

    /* API */

    UFUNCTION(BlueprintCallable)
    UTargetTagRequirementsGameplayEffectComponent* GetOrFindTargetTagRequirementsComponent();

    UFUNCTION(BlueprintCallable)
    UTargetTagsGameplayEffectComponent* GetOrFindTargetTagsGameplayEffectComponent();

protected:
    /* 메서드 */

    void SetModifier(FGameplayModifierInfo*& ModifierPtr, const FGameplayAttribute& Attribute, const FGameplayTag& DataTag, const FName& DataName);
    void RemoveModifier(FGameplayModifierInfo*& ModifierPtr);

protected:
    template<class T>
    TWeakObjectPtr<T> GetOrFindComponent(TWeakObjectPtr<T>& Component) const;
};
