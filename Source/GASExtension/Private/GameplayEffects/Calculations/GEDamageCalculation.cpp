// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/Calculations/GEDamageCalculation.h"

#include "AbilitySystemComponent.h"
#include "GASExtensionSetting.h"
#include "Attributes/GEHealthAttributes.h"
#include "Attributes/GEShieldAttributes.h"
#include "Stats/GEAttackStats.h"
#include "Stats/GEDefenseStats.h"
#include "GEGameplayTags.h"
#include "Logging.h"

using namespace GEGameplayTags;

void UGEDamageCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                  FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    // 유효성 검사
    if(!IsValid(ExecutionParams)) return;

    // 데미지 적용 가능 여부 검사
    if(!CanExecute(ExecutionParams)) return;

    // 지역 변수 선언
    UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
    AActor* SourceActor = SourceASC->GetAvatarActor();
    AActor* TargetActor = TargetASC->GetAvatarActor();
    const float FixedDamage = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(Damage::Root);

    /* 데미지 계산식: Target.Health -= Source.Attack - Target.Defense */
    // Source
    float SourceAttack = SourceASC->GetNumericAttribute(UGEAttackStats::GetAttackAttribute());

    // Target
    float TargetDefense = TargetASC->GetNumericAttribute(UGEDefenseStats::GetDefenseAttribute());
    float TargetShield = TargetASC->GetNumericAttribute(UGEShieldAttributes::GetShieldAttribute());

    // 데미지 계산
    const float TotalDamage = FMath::Max(0, SourceAttack - TargetDefense) + FixedDamage;
    float ShieldDamage = FMath::Min(TotalDamage, TargetShield);
    float HealthDamage = TotalDamage - ShieldDamage;

    // 데미지 반영
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UGEShieldAttributes::GetShieldAttribute(), EGameplayModOp::Additive, -ShieldDamage));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UGEHealthAttributes::GetHealthAttribute(), EGameplayModOp::Additive, -HealthDamage));
}

bool UGEDamageCalculation::IsValid(const FGameplayEffectCustomExecutionParameters& ExecutionParams) const
{
    // ASC 유효성 검사
    UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

    if(SourceASC && TargetASC)
    {
        // AvatarActor 유효성 검사
        AActor* SourceActor = SourceASC->GetAvatarActor();
        AActor* TargetActor = TargetASC->GetAvatarActor();

        if(SourceActor && TargetActor)
        {
            return true;
        }
    }

    return false;
}

bool UGEDamageCalculation::CanExecute(const FGameplayEffectCustomExecutionParameters& ExecutionParams) const
{
    // 지역 변수 선언
    UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

    // 상대가 무적 상태인지 확인
    if(TargetASC->HasMatchingGameplayTag(State::Invinsible)) return false;

    // 상대가 데미지 타입에 대해 면역 상태인지 확인
    if(HasImmunity(TargetASC, GetDamageTypeTag(ExecutionParams.GetOwningSpec()))) return false;

    return true;
}

bool UGEDamageCalculation::HasImmunity(UAbilitySystemComponent* TargetASC, const FDamageTypeTag& DamageTypeTag) const
{
    // 유효성 검사
    if(!DamageTypeTag.IsValid()) return false;

    // 프로젝트 설정 가져오기
    auto Setting = GetMutableDefault<UGASExtensionSetting>();
    const auto& DamageImmunityMap = Setting->DamageImmunityMap;

    // 면역 태그 확인
    bool bResult = DamageImmunityMap.Contains(DamageTypeTag) && TargetASC->HasMatchingGameplayTag(DamageImmunityMap[DamageTypeTag].Tag);

#if WITH_EDITOR
    if(bResult)
    {
        UE_LOG(LogGASExtension, Log, TEXT("%s는 해당 데미지 타입(%s)에 대한 면역이 있습니다."), *TargetASC->GetAvatarActor()->GetName(), *DamageTypeTag.Tag.GetTagName().ToString())
    }
#endif

    return bResult;
}

FDamageTypeTag UGEDamageCalculation::GetDamageTypeTag(const FGameplayEffectSpec& Spec) const
{
    FGameplayTagContainer DamageTypeTags = FGameplayTagContainer(Damage::Type::Root);
    const FGameplayTagContainer& SpecTags = Spec.CapturedSourceTags.GetSpecTags();
    DamageTypeTags = SpecTags.Filter(DamageTypeTags);
    DamageTypeTags.RemoveTag(Damage::Type::Root);

    return DamageTypeTags.IsEmpty() ? FGameplayTag::EmptyTag : DamageTypeTags.First();
}
