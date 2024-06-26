// Fill out your copyright notice in the Description page of Project Settings.

#include "GEBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"
#include "GameplayEffectTypes.h"
#include "GGFGameplayTags.h"
#include "Logging.h"

void UGEBlueprintFunctionLibrary::ApplyDamageToSelf(AActor* Target, TSubclassOf<UGameplayEffect> DamageClass,
    float Damage, float DamageRatio, FGameplayTag DamageTypeTag)
{
    if(Target && DamageClass)
    {
        if(UAbilitySystemComponent* TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target))
        {
            // 데미지 전용 GameplayEffectSpec 생성
            FGameplayEffectContextHandle ContextHandle = TargetSystem->MakeEffectContext();
            FGameplayEffectSpecHandle DamageSpecHandle = TargetSystem->MakeOutgoingSpec(DamageClass, DamageRatio, ContextHandle);
            if(DamageTypeTag.IsValid()) DamageSpecHandle.Data->AddDynamicAssetTag(DamageTypeTag);
            if(Damage > 0) DamageSpecHandle.Data->SetByCallerTagMagnitudes.Emplace(Damage::Root, Damage);

            // 데미지 적용
            TargetSystem->ApplyGameplayEffectSpecToSelf(*DamageSpecHandle.Data.Get());
        }
    }
}

void UGEBlueprintFunctionLibrary::ApplyDamageToTarget(AActor* Source, AActor* Target,
    TSubclassOf<UGameplayEffect> DamageClass, float Damage, float DamageRatio, FGameplayTag DamageTypeTag)
{
    // 지역 변수 선언
    UAbilitySystemComponent* SourceSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Source);
    UAbilitySystemComponent* TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target);

    // 유효성 검사
    if(TargetSystem == nullptr || DamageClass == nullptr) return;

    // 데미지 적용
    if(SourceSystem)
    {
        // 데미지 전용 GameplayEffectSpec 생성
        FGameplayEffectContextHandle ContextHandle = SourceSystem->MakeEffectContext();
        FGameplayEffectSpecHandle DamageSpecHandle = SourceSystem->MakeOutgoingSpec(DamageClass, DamageRatio, ContextHandle);
        if(DamageTypeTag.IsValid()) DamageSpecHandle.Data->AddDynamicAssetTag(DamageTypeTag);
        DamageSpecHandle.Data->SetByCallerTagMagnitudes.Emplace(Damage::Root, FMath::Max(Damage, 0));

        // 적용
        SourceSystem->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), TargetSystem);
    }
    else
    {
#if WITH_EDITOR
        UE_LOG(LogGASExtension, Warning, TEXT("%s::%s > SourceSystem is null"), *StaticClass()->GetName(), *FString(__func__))
#endif
        ApplyDamageToSelf(Target, DamageClass, Damage, DamageRatio, DamageTypeTag);
    }
}

void UGEBlueprintFunctionLibrary::LocalHandleGameplayCue(AActor* EffectCauser, const FGameplayCueTag& CueTag,
    AActor* Target, AActor* Instigator)
{
    // 유효성 검사
    if(EffectCauser == nullptr || !CueTag.IsValid()) return;

    // 기본값 설정
    Target = Target ? Target : EffectCauser;
    Instigator = Instigator ? Instigator : EffectCauser->GetInstigator();

    // 파라미터 설정
    FGameplayCueParameters GameplayCueParameters;
    GameplayCueParameters.EffectCauser = EffectCauser;
    GameplayCueParameters.Instigator = Instigator;
    GameplayCueParameters.Location = Target->GetActorLocation();
    GameplayCueParameters.Normal = Target->GetActorRotation().Vector();

    UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(Target, CueTag.GameplayCueTag, EGameplayCueEvent::Executed, GameplayCueParameters);
}

void UGEBlueprintFunctionLibrary::LocalHandleGameplayCueWithTransform(AActor* EffectCauser,
    const FGameplayCueTag& CueTag, const FTransform& Transform, AActor* Target, AActor* Instigator)
{
    // 유효성 검사
    if(EffectCauser == nullptr || !CueTag.IsValid()) return;

    // 기본값 설정
    Target = Target ? Target : EffectCauser;
    Instigator = Instigator ? Instigator : EffectCauser->GetInstigator();

    // 파라미터 설정
    FGameplayCueParameters GameplayCueParameters;
    GameplayCueParameters.EffectCauser = EffectCauser;
    GameplayCueParameters.Instigator = Instigator;
    GameplayCueParameters.Location = Transform.GetLocation();
    GameplayCueParameters.Normal = Transform.GetRotation().ToRotationVector();

    UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(Target, CueTag.GameplayCueTag, EGameplayCueEvent::Executed, GameplayCueParameters);
}
