// Fill out your copyright notice in the Description page of Project Settings.


#include "GEBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameplayEffectTypes.h"
#include "GEGameplayTags.h"
#include "Logging.h"

using namespace GEGameplayTags;

class UAbilitySystemComponent;

void UGEBlueprintFunctionLibrary::AddAttributeSetToTarget(const TSubclassOf<UAttributeSet> AttributeSetClass, const AActor* TargetActor)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    AddAttributeSetToSystem(AttributeSetClass, AbilitySystem);
}

void UGEBlueprintFunctionLibrary::AddAttributeSetsToTarget(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses,
    const AActor* TargetActor)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    AddAttributeSetsToSystem(AttributeSetClasses, AbilitySystem);
}

void UGEBlueprintFunctionLibrary::AddAttributeSetToSystem(const TSubclassOf<UAttributeSet> AttributeSetClass,
                                         UAbilitySystemComponent* AbilitySystem)
{
    // 유효성 검사
    if(AttributeSetClass == nullptr || AbilitySystem == nullptr) return;

    // AttributeSet 생성 및 등록
    UAttributeSet* Attributes = NewObject<UAttributeSet>(AbilitySystem->GetOwner(), AttributeSetClass);
    AbilitySystem->AddSpawnedAttribute(Attributes);
}

void UGEBlueprintFunctionLibrary::AddAttributeSetsToSystem(const TArray<TSubclassOf<UAttributeSet>>& AttributeSetClasses,
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

FActiveGameplayEffectHandle UGEBlueprintFunctionLibrary::ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* TargetActor)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    return ApplyGameplayEffectToSystem(EffectClass, AbilitySystem);
}

TArray<FActiveGameplayEffectHandle> UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToSelf(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses,
    const AActor* TargetActor)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    return ApplyGameplayEffectsToSystem(EffectClasses, AbilitySystem);
}

FActiveGameplayEffectHandle UGEBlueprintFunctionLibrary::ApplyGameplayEffectToTarget(const TSubclassOf<UGameplayEffect> EffectClass, const AActor* Instigator, const AActor* TargetActor)
{
    UAbilitySystemComponent* InstigatorAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Instigator);
    UAbilitySystemComponent* TargetAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // Instigator가 존재하지 않는 경우 Self로 대신 실행합니다.
    if(InstigatorAbilitySystem == nullptr)
    {
        return ApplyGameplayEffectToSystem(EffectClass, TargetAbilitySystem);
    }
    else
    {
        return ApplyGameplayEffectToTargetSystem(EffectClass, InstigatorAbilitySystem, TargetAbilitySystem);
    }
}

TArray<FActiveGameplayEffectHandle> UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToTarget(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses,
    const AActor* Instigator, const AActor* TargetActor)
{
    UAbilitySystemComponent* InstigatorAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Instigator);
    UAbilitySystemComponent* TargetAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

    // Instigator가 존재하지 않는 경우 Self로 대신 실행합니다.
    if(InstigatorAbilitySystem == nullptr)
    {
        return ApplyGameplayEffectsToSystem(EffectClasses, TargetAbilitySystem);
    }
    else
    {
        return ApplyGameplayEffectsToTargetSystem(EffectClasses, InstigatorAbilitySystem, TargetAbilitySystem);
    }
}

FActiveGameplayEffectHandle UGEBlueprintFunctionLibrary::ApplyGameplayEffectToSystem(const TSubclassOf<UGameplayEffect> EffectClass,
    UAbilitySystemComponent* AbilitySystem)
{
    // 유효성 검사
    if(EffectClass == nullptr || AbilitySystem == nullptr) return FActiveGameplayEffectHandle();

    // Effect 적용
    const UGameplayEffect* Effect = EffectClass->GetDefaultObject<UGameplayEffect>();
    return AbilitySystem->ApplyGameplayEffectToSelf(Effect, UGameplayEffect::INVALID_LEVEL, AbilitySystem->MakeEffectContext());
}

TArray<FActiveGameplayEffectHandle> UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToSystem(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses,
    UAbilitySystemComponent* AbilitySystem)
{
    // 지역 변수 선언
    TArray<FActiveGameplayEffectHandle> Results;
    Results.Reserve(EffectClasses.Num());

    // 유효성 검사
    if(AbilitySystem == nullptr || !AbilitySystem->IsOwnerActorAuthoritative()) return Results;

    // Effects 적용
    for (const TSubclassOf<UGameplayEffect> EffectClass : EffectClasses)
    {
        // null 검사
        if(EffectClass == nullptr) continue;

        // Effect 적용
        Results.Emplace(ApplyGameplayEffectToSystem(EffectClass, AbilitySystem));
    }

    return Results;
}

FActiveGameplayEffectHandle UGEBlueprintFunctionLibrary::ApplyGameplayEffectToTargetSystem(const TSubclassOf<UGameplayEffect> EffectClass,
    UAbilitySystemComponent* InstigatorAbilitySystem, UAbilitySystemComponent* TargetAbilitySystem)
{
    // 유효성 검사
    if(EffectClass == nullptr || TargetAbilitySystem == nullptr) return FActiveGameplayEffectHandle();

    // Instigator AbilitySystem 획득 및 유효성 검사
    if(InstigatorAbilitySystem == nullptr) return ApplyGameplayEffectToSystem(EffectClass, TargetAbilitySystem);

    // Instigator가 Target에게 Effect 적용
    UGameplayEffect* Effect = EffectClass->GetDefaultObject<UGameplayEffect>();
    return InstigatorAbilitySystem->ApplyGameplayEffectToTarget(Effect, TargetAbilitySystem);
}

TArray<FActiveGameplayEffectHandle> UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToTargetSystem(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses,
    UAbilitySystemComponent* Instigator, UAbilitySystemComponent* TargetAbilitySystem)
{
    // 지역 변수 선언
    TArray<FActiveGameplayEffectHandle> Results;
    Results.Reserve(EffectClasses.Num());

    // 서버에서만 호출
    if(Instigator == nullptr || !Instigator->IsOwnerActorAuthoritative()) return Results;

    for (const TSubclassOf<UGameplayEffect> EffectClass : EffectClasses)
    {
        // null 검사
        if(EffectClass == nullptr) continue;

        // Effect 적용
        Results.Emplace(ApplyGameplayEffectToTargetSystem(EffectClass, Instigator, TargetAbilitySystem));
    }

    return Results;
}

FGameplayAbilitySpecHandle UGEBlueprintFunctionLibrary::GiveAbilityToTarget(const TSubclassOf<UGameplayAbility> AbilityClass, const AActor* Target)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target);

    return GiveAbilityToSystem(AbilityClass, AbilitySystem);
}

TArray<FGameplayAbilitySpecHandle> UGEBlueprintFunctionLibrary::GiveAbilitiesToTarget(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses,
    const AActor* Target)
{
    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target);

    return GiveAbilitiesToSystem(AbilityClasses, AbilitySystem);
}

FGameplayAbilitySpecHandle UGEBlueprintFunctionLibrary::GiveAbilityToSystem(const TSubclassOf<UGameplayAbility> AbilityClass,
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

TArray<FGameplayAbilitySpecHandle> UGEBlueprintFunctionLibrary::GiveAbilitiesToSystem(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses,
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
    if(Source && Target && DamageClass)
    {
        UAbilitySystemComponent* SourceSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Source);
        UAbilitySystemComponent* TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target);
        if(SourceSystem && TargetSystem)
        {
            // 데미지 전용 GameplayEffectSpec 생성
            FGameplayEffectContextHandle ContextHandle = SourceSystem->MakeEffectContext();
            FGameplayEffectSpecHandle DamageSpecHandle = SourceSystem->MakeOutgoingSpec(DamageClass, DamageRatio, ContextHandle);
            if(DamageTypeTag.IsValid()) DamageSpecHandle.Data->AddDynamicAssetTag(DamageTypeTag);
            DamageSpecHandle.Data->SetByCallerTagMagnitudes.Emplace(Damage::Root, FMath::Min(Damage, 0));

            // 적용
            SourceSystem->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), TargetSystem);
        }
    }
}

void UGEBlueprintFunctionLibrary::ApplyRadialDamageToSelf(AActor* Target, AActor* ExplosiveActor,
    TSubclassOf<UGameplayEffect> DamageClass, float Damage, FGameplayTag DamageTypeTag, float InnerRadius,
    ECollisionChannel CollisionChannel, bool bShowDebug)
{
    if(Target && DamageClass)
    {
        float DamageRatio = CalculateDamageRatioForExplosion(Target, ExplosiveActor, InnerRadius, CollisionChannel, bShowDebug);
        ApplyDamageToSelf(Target, DamageClass, Damage, DamageRatio, DamageTypeTag);
    }
}

void UGEBlueprintFunctionLibrary::ApplyRadialDamageToTarget(AActor* Source, AActor* Target, AActor* ExplosiveActor,
                                                            TSubclassOf<UGameplayEffect> DamageClass, float Damage, FGameplayTag DamageTypeTag,
                                                            float InnerRadius, ECollisionChannel CollisionChannel, bool bShowDebug)
{
    if(Source && Target && DamageClass)
    {
        float DamageRatio = CalculateDamageRatioForExplosion(Target, ExplosiveActor, InnerRadius, CollisionChannel, bShowDebug);
        ApplyDamageToTarget(Source, Target, DamageClass, Damage, DamageRatio, DamageTypeTag);
    }
}

float UGEBlueprintFunctionLibrary::CalculateDamageRatioForExplosion(AActor* Target, AActor* ExplosiveActor, float InnerRadius, ECollisionChannel CollisionChannel, bool bShowDebug)
{
    bShowDebug = true;

    const FVector& ExplosionOrigin = ExplosiveActor->GetActorLocation();

    /* 피격 판정에 따른 데미지 배율 계산 */
    // 피격 카운트
    int32 Count = 0;

    // 피격 판정을 위한 위치 지정 (자기 자신도 포함됩니다)
    TArray<FVector> TargetLocations;
    GetLocationsForExplosionDetection(Target, TargetLocations);

    // 라인 트레이스로 피격 판정
    for (const FVector& TargetLocation : TargetLocations)
    {
        if(UWorld* World = Target->GetWorld())
        {
            FCollisionQueryParams CollisionQueryParams;
            CollisionQueryParams.AddIgnoredActor(ExplosiveActor);
            const FVector& Direction = (TargetLocation - ExplosionOrigin).GetSafeNormal();
            const float Offset = 100.f;
            const FVector TraceEnd = TargetLocation + Direction * Offset;

            FHitResult HitResult;
            World->LineTraceSingleByChannel(
                HitResult,
                ExplosionOrigin,
                TraceEnd,
                CollisionChannel,
                CollisionQueryParams
                );

            // 피격 대상이 동일, 즉 장애물이 없는 경우
            if(HitResult.GetActor() == Target)
            {
#if WITH_EDITOR
                if(bShowDebug)
                    DrawDebugLine(
                        World,
                        ExplosionOrigin,
                        TraceEnd,
                        FColor::Green,
                        false,
                        3,
                        0,
                        2
                        );
#endif
                // 피격 카운트 추가
                Count++;
            }
            else
            {
#if WITH_EDITOR
                if(bShowDebug)
                    DrawDebugLine(
                        World,
                        ExplosionOrigin,
                        TraceEnd,
                        FColor::Red,
                        false,
                        3,
                        0,
                        2
                        );
#endif
            }
        }
    }

    // 피격 판정 비율
    float HitRatio = Count == 0 ? 0 : Count / static_cast<float>(TargetLocations.Num());

    /* 거리 별 데미지 비율 계산 */
    float Distance = (Target->GetActorLocation() - ExplosionOrigin).Size();
    float DistanceRatio = Distance <= InnerRadius ? 1 : InnerRadius / Distance;

    /* 최종 데미지 배율 */
    float DamageRatio = HitRatio * DistanceRatio;

#if WITH_EDITOR
    UE_LOG(LogGASExtension, Log, TEXT("%s > DamageRatio(%f) = HitRatio(%f) * DistanceRatio(%f)"), *Target->GetName(), DamageRatio, HitRatio, DistanceRatio)
#endif

    return DamageRatio;
}

void UGEBlueprintFunctionLibrary::GetLocationsForExplosionDetection(AActor* Target,
                                                                    TArray<FVector>& TargetLocations)
{
    // null 검사
    if(Target == nullptr) return;

    // 배열 비우기
    TargetLocations.Reset(5);

    // 타깃 액터 바운드 가져오기
    float CollisionRadius;
    float CollisionHalfHeight;
    Target->GetComponentsBoundingCylinder(CollisionRadius, CollisionHalfHeight);

    // 기준 벡터 캐싱
    const FVector& UpVector = Target->GetActorUpVector();
    const FVector& RightVector = Target->GetActorRightVector();

    // TODO Offset 비율 조정은 임의로 했기 때문에 피격 판정이 이상한 경우 이 부분을 의심해보아야 합니다.
    const FVector UpOffset = CollisionHalfHeight * UpVector * 0.8f;
    const FVector RightOffset = CollisionRadius * RightVector * 0.3f;

    // 상하좌우 지점 구하기
    const FVector& TargetCenter = Target->GetActorLocation();
    const FVector TopLocation = TargetCenter + UpOffset;
    const FVector BottomLocation = TargetCenter - UpOffset;
    const FVector RightLocation = TargetCenter + RightOffset;
    const FVector LeftLocation = TargetCenter - RightOffset;

    // 배열 반환
    TargetLocations.Add(TargetCenter);
    TargetLocations.Add(TopLocation);
    TargetLocations.Add(BottomLocation);
    TargetLocations.Add(LeftLocation);
    TargetLocations.Add(RightLocation);
}
