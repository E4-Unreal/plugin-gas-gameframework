// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"
#include "GameplayEffect.h"
#include "GGFGameplayTags.h"
#include "Logging.h"

FActiveGameplayEffectHandle UGGFBlueprintFunctionLibrary::ApplyGameplayEffectSpecToSelf(const AActor* TargetActor,
    const FGameplayEffectSpec& EffectSpec)
{
    // 지역 변수 정의
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr) return FActiveGameplayEffectHandle();

    // 게임플레이 이펙트 적용
    return TargetSystem->ApplyGameplayEffectSpecToSelf(EffectSpec);
}

TArray<FActiveGameplayEffectHandle> UGGFBlueprintFunctionLibrary::ApplyGameplayEffectSpecsToSelf(const AActor* TargetActor,
    const TArray<FGameplayEffectSpec>& EffectSpecs)
{
    // 지역 변수 정의
    TArray<FActiveGameplayEffectHandle> Results;
    Results.Reserve(EffectSpecs.Num());
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr || EffectSpecs.IsEmpty()) return Results;

    // 게임플레이 이펙트 적용
    for (const auto& EffectSpec : EffectSpecs)
    {
        Results.Emplace(ApplyGameplayEffectSpecToSelf(TargetActor, EffectSpec));
    }

    return Results;
}

FActiveGameplayEffectHandle UGGFBlueprintFunctionLibrary::ApplyGameplayEffectSpecToTarget(const AActor* InstigatorActor,
    const AActor* TargetActor, const FGameplayEffectSpec& EffectSpec)
{
    // 지역 변수 정의
    auto SourceSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(InstigatorActor);
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr) return FActiveGameplayEffectHandle();

    // 게임플레이 이펙트 적용
    return SourceSystem ? SourceSystem->ApplyGameplayEffectSpecToTarget(EffectSpec, TargetSystem) : ApplyGameplayEffectSpecToSelf(TargetActor, EffectSpec);
}

TArray<FActiveGameplayEffectHandle> UGGFBlueprintFunctionLibrary::ApplyGameplayEffectSpecsToTarget(
    const AActor* InstigatorActor, const AActor* TargetActor, const TArray<FGameplayEffectSpec>& EffectSpecs)
{
    // 지역 변수 정의
    TArray<FActiveGameplayEffectHandle> Results;
    Results.Emplace(EffectSpecs.Num());
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr || EffectSpecs.IsEmpty()) return Results;

    // 게임플레이 이펙트 적용
    for (auto EffectSpec : EffectSpecs)
    {
        Results.Emplace(ApplyGameplayEffectSpecToTarget(InstigatorActor, TargetActor, EffectSpec));
    }

    return Results;
}

FActiveGameplayEffectHandle UGGFBlueprintFunctionLibrary::ApplyGameplayEffectToSelf(const AActor* TargetActor,
                                                                                    const TSubclassOf<UGameplayEffect> EffectClass)
{
    // 지역 변수 정의
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr || EffectClass == nullptr) return FActiveGameplayEffectHandle();

    // 게임플레이 이펙트 적용
    return TargetSystem->ApplyGameplayEffectToSelf(EffectClass->GetDefaultObject<UGameplayEffect>(), FGameplayEffectConstants::INVALID_LEVEL, TargetSystem->MakeEffectContext());
}

TArray<FActiveGameplayEffectHandle> UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToSelf(const AActor* TargetActor,
    const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses)
{
    // 지역 변수 선언
    TArray<FActiveGameplayEffectHandle> Results;
    Results.Reserve(EffectClasses.Num());
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr || EffectClasses.IsEmpty()) return Results;

    // 게임플레이 이펙트 적용
    for (auto EffectClass : EffectClasses)
    {
        Results.Emplace(ApplyGameplayEffectToSelf(TargetActor, EffectClass));
    }

    return Results;
}

FActiveGameplayEffectHandle UGGFBlueprintFunctionLibrary::ApplyGameplayEffectToTarget(const AActor* InstigatorActor,
    const AActor* TargetActor, const TSubclassOf<UGameplayEffect> EffectClass)
{
    // 지역 변수 정의
    auto SourceSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(InstigatorActor);
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr || EffectClass == nullptr) return FActiveGameplayEffectHandle();

    // 게임플레이 이펙트 적용
    return SourceSystem ? SourceSystem->ApplyGameplayEffectToTarget(EffectClass->GetDefaultObject<UGameplayEffect>(), TargetSystem) : ApplyGameplayEffectToSelf(TargetActor, EffectClass);
}

TArray<FActiveGameplayEffectHandle> UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToTarget(
    const AActor* InstigatorActor, const AActor* TargetActor, const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses)
{
    // 지역 변수 정의
    TArray<FActiveGameplayEffectHandle> Results;
    Results.Emplace(EffectClasses.Num());
    auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // 입력 유효성 검사
    if(TargetSystem == nullptr || EffectClasses.IsEmpty()) return Results;

    // 게임플레이 이펙트 적용
    for (auto EffectClass : EffectClasses)
    {
        Results.Emplace(ApplyGameplayEffectToTarget(InstigatorActor, TargetActor, EffectClass));
    }

    return Results;
}

void UGGFBlueprintFunctionLibrary::AddAttributeSetToTarget(const TSubclassOf<UAttributeSet> AttributeSetClass, const AActor* TargetActor)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    AddAttributeSetToSystem(AttributeSetClass, AbilitySystem);
}

void UGGFBlueprintFunctionLibrary::AddAttributeSetsToTarget(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses,
    const AActor* TargetActor)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    AddAttributeSetsToSystem(AttributeSetClasses, AbilitySystem);
}

void UGGFBlueprintFunctionLibrary::AddAttributeSetToSystem(const TSubclassOf<UAttributeSet> AttributeSetClass,
                                         UAbilitySystemComponent* AbilitySystem)
{
    // 유효성 검사
    if(AttributeSetClass == nullptr || AbilitySystem == nullptr) return;

    // AttributeSet 생성 및 등록
    UAttributeSet* Attributes = NewObject<UAttributeSet>(AbilitySystem->GetOwner(), AttributeSetClass);
    AbilitySystem->AddSpawnedAttribute(Attributes);
}

void UGGFBlueprintFunctionLibrary::AddAttributeSetsToSystem(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses,
    UAbilitySystemComponent* AbilitySystem)
{
    // 유효성 검사
    if(AbilitySystem == nullptr) return;

    // AttributeSet 생성 및 등록
    for (const TSubclassOf<UAttributeSet> AttributeSetClass : AttributeSetClasses)
    {
        AddAttributeSetToSystem(AttributeSetClass, AbilitySystem);
    }
}

FGameplayAbilitySpecHandle UGGFBlueprintFunctionLibrary::GiveAbilityToTarget(const TSubclassOf<UGameplayAbility> AbilityClass, const AActor* Target)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target);

    return GiveAbilityToSystem(AbilityClass, AbilitySystem);
}

TArray<FGameplayAbilitySpecHandle> UGGFBlueprintFunctionLibrary::GiveAbilitiesToTarget(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses,
    const AActor* Target)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target);

    return GiveAbilitiesToSystem(AbilityClasses, AbilitySystem);
}

FGameplayAbilitySpecHandle UGGFBlueprintFunctionLibrary::GiveAbilityToSystem(const TSubclassOf<UGameplayAbility> AbilityClass,
                                             UAbilitySystemComponent* AbilitySystem)
{
    // null 검사
    if(AbilityClass == nullptr || AbilitySystem == nullptr) return FGameplayAbilitySpecHandle();

    // GameplayAbilitySpec 생성
    FGameplayAbilitySpec AbilitySpec = AbilitySystem->BuildAbilitySpecFromClass(AbilityClass);

    // 유효성 검사
    if (!IsValid(AbilitySpec.Ability)) return AbilitySpec.Handle;

    // 어빌리티 부여
    return AbilitySystem->GiveAbility(AbilitySpec);
}

TArray<FGameplayAbilitySpecHandle> UGGFBlueprintFunctionLibrary::GiveAbilitiesToSystem(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses,
    UAbilitySystemComponent* AbilitySystem)
{
    // 변수 선언
    TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

    // 유효성 검사
    if(AbilityClasses.IsEmpty() || AbilitySystem == nullptr) return AbilitySpecHandles;

    // 서버에서만 호출 가능
    if(!AbilitySystem->IsOwnerActorAuthoritative()) return AbilitySpecHandles;

    // 어빌리티 부여
    AbilitySpecHandles.Reserve(AbilityClasses.Num());
    for (const TSubclassOf<UGameplayAbility> AbilityClass : AbilityClasses)
    {
        const FGameplayAbilitySpecHandle& Handle = GiveAbilityToSystem(AbilityClass, AbilitySystem);
        if(Handle.IsValid()) AbilitySpecHandles.Add(Handle);
    }

    return AbilitySpecHandles;
}

void UGGFBlueprintFunctionLibrary::ApplyDamageToSelf(AActor* Target, TSubclassOf<UGameplayEffect> DamageClass,
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
            if(Damage > 0) DamageSpecHandle.Data->SetByCallerTagMagnitudes.Emplace(Data::Damage::Root, Damage);

            // 데미지 적용
            TargetSystem->ApplyGameplayEffectSpecToSelf(*DamageSpecHandle.Data.Get());
        }
    }
}

void UGGFBlueprintFunctionLibrary::ApplyDamageToTarget(AActor* Source, AActor* Target,
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
        DamageSpecHandle.Data->SetByCallerTagMagnitudes.Emplace(Data::Damage::Root, FMath::Max(Damage, 0));

        // 적용
        SourceSystem->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), TargetSystem);
    }
    else
    {
#if WITH_EDITOR
        LOG(Warning, TEXT("%s::%s > SourceSystem is null"), *StaticClass()->GetName(), *FString(__func__))
#endif
        ApplyDamageToSelf(Target, DamageClass, Damage, DamageRatio, DamageTypeTag);
    }
}

void UGGFBlueprintFunctionLibrary::LocalHandleGameplayCue(AActor* EffectCauser, const FGameplayCueTag& CueTag,
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

void UGGFBlueprintFunctionLibrary::LocalHandleGameplayCueWithTransform(AActor* EffectCauser,
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
