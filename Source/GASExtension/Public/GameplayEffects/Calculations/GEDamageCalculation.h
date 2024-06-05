// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEDamageCalculation.generated.h"

struct FDamageTypeTag;

/**
 * 가장 기본적인 데미지 계산식입니다.
 *
 * 총 데미지: 공격 주체의 공격력 - 공격 대상의 방어력
 * 데미지 계산: (공격 대상의 체력 + 방어막) - 데미지
 * 방어막 수치가 먼저 소모되며 0 도달 이후 체력 수치가 소모됩니다.
 *
 * DamageImmunityMap에서 특정 데미지 타입에 대한 면역 기능을 설정할 수 있습니다.
 * 대상에 면역 기능을 부여하는 방법은 면역 태그를 부여하는 것입니다.
 *
 * 데미지 타입 검사는 GameplayEffectSpec의 태그 목록에서 이루어집니다.
 */
UCLASS()
class GASEXTENSION_API UGEDamageCalculation : public UGameplayEffectExecutionCalculation
{
    GENERATED_BODY()

protected:
    // 이곳에 설정된 태그 중 하나라도 Target에 존재하는 경우 데미지를 적용하지 않습니다.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    FGameplayTagContainer IgnoreTagContainer;

public:
    UGEDamageCalculation();

    /* GameplayEffectExecutionCalculation */

    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:
    // ExecutionParams 유효성 검사
    virtual bool IsValid(const FGameplayEffectCustomExecutionParameters& ExecutionParams) const;

    // 데미지 적용 가능 여부 검사
    virtual bool CanExecute(const FGameplayEffectCustomExecutionParameters& ExecutionParams) const;

    // 데미지 타입에 대해 면역 상태인지 확인
    virtual bool HasImmunity(UAbilitySystemComponent* TargetASC, const FDamageTypeTag& DamageTypeTag) const;

    // GameplayEffectSpec에 추가된 AssetTags로부터 DamageTypeTag 가져오기
    virtual FDamageTypeTag GetDamageTypeTag(const FGameplayEffectSpec& Spec) const;

    // 데미지 계산
    virtual float CalculateTotalDamage(const FGameplayEffectCustomExecutionParameters& ExecutionParams, UAbilitySystemComponent* SourceSystem, UAbilitySystemComponent* TargetSystem) const;
};
