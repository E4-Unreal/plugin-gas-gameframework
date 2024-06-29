// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/Calculations/GGFStatDamageCalculation.h"

#include "Logging.h"
#include "GGFGameplayTags.h"
#include "Attributes/GGFHealthAttributes.h"
#include "Stats/GGFAttackStats.h"
#include "Stats/GGFDefenseStats.h"

float UGGFStatDamageCalculation::CalculateTotalDamage(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                      UAbilitySystemComponent* SourceSystem, UAbilitySystemComponent* TargetSystem) const
{
    // 지역 변수 선언
    const FGameplayEffectSpec& OwningSpec = ExecutionParams.GetOwningSpec();
    float TotalDamage = 0;
    float GenericDamage = OwningSpec.GetSetByCallerMagnitude(Data::Damage::Root, false);
    if(auto ModifiedAttribute = OwningSpec.GetModifiedAttribute(UGGFHealthAttributes::GetDamageAttribute()))
    {
        GenericDamage += ModifiedAttribute->TotalMagnitude;
    }
    float TrueDamage = OwningSpec.GetSetByCallerMagnitude(Data::Damage::True, false);
    float StatsDamage = GenericDamage;

    // Target 스탯 가져오기
    const float TargetDefense = TargetSystem->GetNumericAttribute(UGGFDefenseStats::GetDefenseAttribute());

    // Source 검사
    if(SourceSystem && SourceSystem != TargetSystem)
    {
        // Source 스탯 가져오기
        const float SourceAttack = SourceSystem->GetNumericAttribute(UGGFAttackStats::GetAttackAttribute());
        StatsDamage += SourceAttack;
    }

    // 스탯 데미지 계산
    StatsDamage = FMath::Max(0, StatsDamage - TargetDefense);

    // 총 데미지 계산
    TotalDamage = StatsDamage + TrueDamage;

    // 데미지 배율 적용
    const float DamageRatio = OwningSpec.GetLevel() == UGameplayEffect::INVALID_LEVEL ? 1 : OwningSpec.GetLevel();
    TotalDamage *= DamageRatio;

    // Clamp
    TotalDamage = FMath::Max(TotalDamage, 0);

#if WITH_EDITOR
    LOG(Log, TEXT("%s Take Damage From %s: TotalDamage(%f) = (StatsDamage(%f) + TrueDamage(%f)) * DamageRatio(%f)"), *TargetSystem->GetAvatarActor()->GetName(), *SourceSystem->GetAvatarActor()->GetName(), TotalDamage, StatsDamage, TrueDamage, DamageRatio)
#endif

    return TotalDamage;
}
