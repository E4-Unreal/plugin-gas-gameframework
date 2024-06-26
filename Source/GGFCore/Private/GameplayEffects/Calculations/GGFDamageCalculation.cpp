// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/Calculations/GGFDamageCalculation.h"

#include "AbilitySystemComponent.h"
#include "GGFCoreSetting.h"
#include "Attributes/GGFHealthAttributes.h"
#include "Attributes/GGFShieldAttributes.h"
#include "Stats/GGFAttackStats.h"
#include "Stats/GGFDefenseStats.h"
#include "GGFGameplayTags.h"
#include "Logging.h"

UGGFDamageCalculation::UGGFDamageCalculation()
{
    IgnoreTagContainer.AddLeafTag(State::Dead);
    IgnoreTagContainer.AddLeafTag(State::Buff::Invinsible);
}

void UGGFDamageCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                  FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    // 유효성 검사
    if(!IsValid(ExecutionParams)) return;

    // 데미지 적용 가능 여부 검사
    if(!CanExecute(ExecutionParams)) return;

    // 데미지 계산
    UAbilitySystemComponent* TargetSystem = ExecutionParams.GetTargetAbilitySystemComponent();
    UAbilitySystemComponent* SourceSystem = ExecutionParams.GetSourceAbilitySystemComponent();
    const float TotalDamage = CalculateTotalDamage(ExecutionParams, SourceSystem, TargetSystem);

    // Attribute 별 데미지 계산
    float TargetShield = TargetSystem->GetNumericAttribute(UGGFShieldAttributes::GetShieldAttribute());
    float ShieldDamage = FMath::Min(TotalDamage, TargetShield);
    float HealthDamage = TotalDamage - ShieldDamage;

    // 데미지 반영
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UGGFShieldAttributes::GetShieldAttribute(), EGameplayModOp::Additive, -ShieldDamage));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UGGFHealthAttributes::GetHealthAttribute(), EGameplayModOp::Additive, -HealthDamage));
}

bool UGGFDamageCalculation::IsValid(const FGameplayEffectCustomExecutionParameters& ExecutionParams) const
{
    UAbilitySystemComponent* SourceSystem = ExecutionParams.GetSourceAbilitySystemComponent();
    UAbilitySystemComponent* TargetSystem = ExecutionParams.GetTargetAbilitySystemComponent();
    if(SourceSystem && TargetSystem)
    {
        AActor* SourceActor = SourceSystem->GetAvatarActor();
        AActor* TargetActor = TargetSystem->GetAvatarActor();
        if(SourceActor && TargetActor)
        {
            return true;
        }
    }

    return false;
}

bool UGGFDamageCalculation::CanExecute(const FGameplayEffectCustomExecutionParameters& ExecutionParams) const
{
    // 지역 변수 선언
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

    // 상대가 데미지 무시 태그를 가지고 있는지 확인
    if(TargetASC->HasAnyMatchingGameplayTags(IgnoreTagContainer)) return false;

    // 상대가 데미지 타입에 대해 면역 상태인지 확인
    if(HasImmunity(TargetASC, GetDamageTypeTag(ExecutionParams.GetOwningSpec()))) return false;

    return true;
}

bool UGGFDamageCalculation::HasImmunity(UAbilitySystemComponent* TargetASC, const FGGFDamageTypeTag& DamageTypeTag) const
{
    // 유효성 검사
    if(!DamageTypeTag.IsValid()) return false;

    // 프로젝트 설정 가져오기
    auto Setting = GetMutableDefault<UGGFCoreSetting>();
    const auto& DamageImmunityMap = Setting->DamageImmunityMap;

    // 면역 태그 확인
    bool bResult = DamageImmunityMap.Contains(DamageTypeTag) && TargetASC->HasMatchingGameplayTag(DamageImmunityMap[DamageTypeTag].Tag);

#if WITH_EDITOR
    if(bResult)
    {
        LOG(Log, TEXT("%s는 해당 데미지 타입(%s)에 대한 면역이 있습니다."), *TargetASC->GetAvatarActor()->GetName(), *DamageTypeTag.Tag.GetTagName().ToString())
    }
#endif

    return bResult;
}

FGGFDamageTypeTag UGGFDamageCalculation::GetDamageTypeTag(const FGameplayEffectSpec& Spec) const
{
    FGameplayTagContainer DamageTypeTags = FGameplayTagContainer(Data::Damage::Type::Root);
    const FGameplayTagContainer& SpecTags = Spec.CapturedSourceTags.GetSpecTags();
    DamageTypeTags = SpecTags.Filter(DamageTypeTags);
    DamageTypeTags.RemoveTag(Data::Damage::Type::Root);

    return DamageTypeTags.IsEmpty() ? FGameplayTag::EmptyTag : DamageTypeTags.First();
}

float UGGFDamageCalculation::CalculateTotalDamage(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
    UAbilitySystemComponent* SourceSystem, UAbilitySystemComponent* TargetSystem) const
{
    // 지역 변수 선언
    const FGameplayEffectSpec& OwningSpec = ExecutionParams.GetOwningSpec();
    float TotalDamage = 0;
    float GenericDamage = OwningSpec.GetSetByCallerMagnitude(Data::Damage::Root, false);
    float TrueDamage = OwningSpec.GetSetByCallerMagnitude(Data::Damage::True, false);
    float StatsDamage = GenericDamage;

    if(auto ModifiedAttribute = OwningSpec.GetModifiedAttribute(UGGFHealthAttributes::GetDamageAttribute()))
    {
        GenericDamage += ModifiedAttribute->TotalMagnitude;
    }

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
