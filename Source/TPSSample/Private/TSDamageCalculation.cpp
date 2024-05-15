// Fill out your copyright notice in the Description page of Project Settings.

#include "TSDamageCalculation.h"

#include "AbilitySystemComponent.h"
#include "Attributes/GEHealthAttributes.h"
#include "Attributes/GEShieldAttributes.h"
#include "Stats/GEAttackStats.h"
#include "Stats/GEDefenseStats.h"

void UTSDamageCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                      FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

    UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

    if(SourceASC && TargetASC)
    {
        AActor* SourceActor = SourceASC->GetAvatarActor();
        AActor* TargetActor = TargetASC->GetAvatarActor();

        if(SourceActor && TargetActor)
        {
            /* 데미지 계산식: Target.Health -= Source.Attack - Target.Defense */
            // Source
            float SourceAttack = SourceASC->GetNumericAttribute(UGEAttackStats::GetAttackAttribute());

            // Target
            float TargetDefense = TargetASC->GetNumericAttribute(UGEDefenseStats::GetDefenseAttribute());
            float TargetShield = TargetASC->GetNumericAttribute(UGEShieldAttributes::GetShieldAttribute());

            // 데미지 계산
            const float TotalDamage = FMath::Max(0, SourceAttack - TargetDefense);
            float ShieldDamage = FMath::Min(TotalDamage, TargetShield);
            float HealthDamage = TotalDamage - ShieldDamage;

            // 데미지 반영
            OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UGEShieldAttributes::GetShieldAttribute(), EGameplayModOp::Additive, -ShieldDamage));
            OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UGEHealthAttributes::GetHealthAttribute(), EGameplayModOp::Additive, -HealthDamage));
        }
    }
}
