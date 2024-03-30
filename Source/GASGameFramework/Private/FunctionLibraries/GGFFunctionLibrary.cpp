// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/GGFFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Logging.h"

class UAbilitySystemComponent;

void UGGFFunctionLibrary::AddAttributeSetToTarget(const TSubclassOf<UAttributeSet> AttributeSetClass, const AActor* TargetActor)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    AddAttributeSetToSystem(AttributeSetClass, AbilitySystem);
}

void UGGFFunctionLibrary::AddAttributeSetsToTarget(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses,
    const AActor* TargetActor)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    AddAttributeSetsToSystem(AttributeSetClasses, AbilitySystem);
}

void UGGFFunctionLibrary::AddAttributeSetToSystem(const TSubclassOf<UAttributeSet> AttributeSetClass,
                                         UAbilitySystemComponent* AbilitySystem)
{
    // 유효성 검사
    if(AttributeSetClass == nullptr || AbilitySystem == nullptr) return;

    // AttributeSet 생성 및 등록
    UAttributeSet* Attributes = NewObject<UAttributeSet>(AbilitySystem->GetOwner(), AttributeSetClass);
    AbilitySystem->AddSpawnedAttribute(Attributes);
}

void UGGFFunctionLibrary::AddAttributeSetsToSystem(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses,
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

void UGGFFunctionLibrary::ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* TargetActor)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    ApplyGameplayEffectToSystem(EffectClass, AbilitySystem);
}

void UGGFFunctionLibrary::ApplyGameplayEffectsToSelf(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses,
    const AActor* TargetActor)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    ApplyGameplayEffectsToSystem(EffectClasses, AbilitySystem);
}

void UGGFFunctionLibrary::ApplyGameplayEffectToTarget(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* Instigator, const AActor* TargetActor)
{
    UAbilitySystemComponent* InstigatorAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Instigator);
    UAbilitySystemComponent* TargetAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // Instigator가 존재하지 않는 경우 Self로 대신 실행합니다.
    if(InstigatorAbilitySystem == nullptr)
        ApplyGameplayEffectToSystem(EffectClass, TargetAbilitySystem);
    else
        ApplyGameplayEffectToTargetSystem(EffectClass, InstigatorAbilitySystem, TargetAbilitySystem);
}

void UGGFFunctionLibrary::ApplyGameplayEffectsToTarget(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses,
    const AActor* Instigator, const AActor* TargetActor)
{
    UAbilitySystemComponent* InstigatorAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Instigator);
    UAbilitySystemComponent* TargetAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // Instigator가 존재하지 않는 경우 Self로 대신 실행합니다.
    if(InstigatorAbilitySystem == nullptr)
        ApplyGameplayEffectsToSystem(EffectClasses, TargetAbilitySystem);
    else
        ApplyGameplayEffectsToTargetSystem(EffectClasses, InstigatorAbilitySystem, TargetAbilitySystem);
}

void UGGFFunctionLibrary::ApplyGameplayEffectToSystem(const TSubclassOf<UGameplayEffect> EffectClass,
    UAbilitySystemComponent* AbilitySystem)
{
    // 유효성 검사
    if(EffectClass == nullptr || AbilitySystem == nullptr) return;

    // Effect 적용
    const UGameplayEffect* Effect = EffectClass->GetDefaultObject<UGameplayEffect>();
    AbilitySystem->ApplyGameplayEffectToSelf(Effect, UGameplayEffect::INVALID_LEVEL, AbilitySystem->MakeEffectContext());
}

void UGGFFunctionLibrary::ApplyGameplayEffectsToSystem(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses,
    UAbilitySystemComponent* AbilitySystem)
{
    // 유효성 검사
    if(AbilitySystem == nullptr || !AbilitySystem->IsOwnerActorAuthoritative()) return;

    // Effects 적용
    for (const TSubclassOf<UGameplayEffect> EffectClass : EffectClasses)
    {
        // null 검사
        if(EffectClass == nullptr) continue;

        // Effect 적용
        ApplyGameplayEffectToSystem(EffectClass, AbilitySystem);
    }
}

void UGGFFunctionLibrary::ApplyGameplayEffectToTargetSystem(const TSubclassOf<UGameplayEffect> EffectClass,
    UAbilitySystemComponent* Instigator, UAbilitySystemComponent* TargetAbilitySystem)
{
    // Instigator AbilitySystem 획득 및 유효성 검사
    if(Instigator == nullptr)
    {
#if WITH_EDITOR
        LOG_CHECK(LogGASGameFramework, Instigator == nullptr);
#endif

        ApplyGameplayEffectToSystem(EffectClass, TargetAbilitySystem);
        return;
    }

    // Instigator가 Target에게 Effect 적용
    UGameplayEffect* Effect = EffectClass->GetDefaultObject<UGameplayEffect>();
    Instigator->ApplyGameplayEffectToTarget(Effect, TargetAbilitySystem);
}

void UGGFFunctionLibrary::ApplyGameplayEffectsToTargetSystem(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses,
    UAbilitySystemComponent* Instigator, UAbilitySystemComponent* TargetAbilitySystem)
{
    // 서버에서만 호출
    if(Instigator == nullptr || !Instigator->IsOwnerActorAuthoritative()) return;

    for (const TSubclassOf<UGameplayEffect> EffectClass : EffectClasses)
    {
        // null 검사
        if(EffectClass == nullptr) continue;

        // Effect 적용
        ApplyGameplayEffectToTargetSystem(EffectClass, Instigator, TargetAbilitySystem);
    }
}

FGameplayAbilitySpecHandle UGGFFunctionLibrary::GiveAbilityToTarget(const TSubclassOf<UGameplayAbility> AbilityClass, const AActor* Target)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target);

    return GiveAbilityToSystem(AbilityClass, AbilitySystem);
}

TArray<FGameplayAbilitySpecHandle> UGGFFunctionLibrary::GiveAbilitiesToTarget(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses,
    const AActor* Target)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target);

    return GiveAbilitiesToSystem(AbilityClasses, AbilitySystem);
}

FGameplayAbilitySpecHandle UGGFFunctionLibrary::GiveAbilityToSystem(const TSubclassOf<UGameplayAbility> AbilityClass,
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

TArray<FGameplayAbilitySpecHandle> UGGFFunctionLibrary::GiveAbilitiesToSystem(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses,
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
