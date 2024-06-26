﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "GGFGameplayTags.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"

UGGFGameplayAbility::UGGFGameplayAbility()
{
    /* 기본 설정 */

    // 인스턴싱 정책
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    // 실행 정책
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;

    // 입력 리플리케이트
    bReplicateInputDirectly = true;

    /* 태그 설정 */

    // 입력 태그 설정
    InputTag = Input::Test;
    CooldownTag = Skill::Cooldown::Test;

    // 기본 어빌리티 태그 설정
    AbilityTags.AddTagFast(Action::Root);
    ActivationOwnedTags.AddTagFast(Action::Root);

    // ActivationBlockedTags 설정
    ActivationBlockedTags.AddTagFast(Action::Root);
    ActivationBlockedTags.AddTagFast(State::Dead);
    ActivationBlockedTags.AddTagFast(State::Knockdown);
    ActivationBlockedTags.AddTagFast(State::Debuff::Stun);
}

bool UGGFGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
    const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
    if(InstancingPolicy == EGameplayAbilityInstancingPolicy::InstancedPerActor)
    {
        auto AbilitySpec = ActorInfo->AbilitySystemComponent->FindAbilitySpecFromHandle(Handle);
        auto AbilityInstance = CastChecked<UGGFGameplayAbility>(AbilitySpec->GetPrimaryInstance());

        return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) && AbilityInstance->bValid && AbilityInstance->InternalCanActivate();
    }

    return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UGGFGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

     if(!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
    }
}

void UGGFGameplayAbility::InputPressed(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    Super::InputPressed(Handle, ActorInfo, ActivationInfo);

    // TODO 의도한대로 동작하지 않습니다. 아직은 크게 중요하지 않은 사항이기 때문에 나중에 수정할 예정입니다.
    // 어빌리티 입력이 활성화되었지만 어빌리티가 활성화되지 않은 경우 실패한 것으로 간주하여 어빌리티 입력을 초기화합니다.
    GetCurrentAbilitySpec()->InputPressed = GetCurrentAbilitySpec()->IsActive();
}

void UGGFGameplayAbility::InputReleased(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    Super::InputReleased(Handle, ActorInfo, ActivationInfo);

    // 어빌리티 입력이 비활성화되면 어빌리티를 종료합니다.
    if(bCancelableByInputRelease && GetCurrentAbilitySpec()->IsActive()) CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void UGGFGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnGiveAbility(ActorInfo, Spec);

    CreateCooldownEffectInstance();
}

void UGGFGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
    if(UGameplayEffect* CooldownGE = GetCooldownGameplayEffect())
    {
        auto Context = ActorInfo->AbilitySystemComponent->MakeEffectContext();
        auto NewSpec = new FGameplayEffectSpec(CooldownGE, Context, GetAbilityLevel());
        ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, FGameplayEffectSpecHandle(NewSpec));
    }
}

UGameplayEffect* UGGFGameplayAbility::GetCooldownGameplayEffect() const
{
    if(CooldownEffectInstance) return CooldownEffectInstance;

    return Super::GetCooldownGameplayEffect();
}

void UGGFGameplayAbility::CreateCooldownEffectInstance()
{
    // 쿨다운 시간이 설정된 경우
    if(!FMath::IsNearlyZero(CooldownTime))
    {
        // 쿨다운 게임플레이 이펙트 인스턴스 생성
        UGameplayEffect* NewCooldown = NewObject<UGameplayEffect>(this, *(GetName() + " Cooldown"));
        NewCooldown->DurationPolicy = EGameplayEffectDurationType::HasDuration;
        NewCooldown->DurationMagnitude = FGameplayEffectModifierMagnitude(CooldownTime);
        TObjectPtr<UTargetTagsGameplayEffectComponent> TargetTagsComponent = &NewCooldown->AddComponent<UTargetTagsGameplayEffectComponent>();
        FInheritedTagContainer TagContainer;
        TagContainer.Added.AddTag(CooldownTag);
        TargetTagsComponent->SetAndApplyTargetTagChanges(TagContainer);

        CooldownEffectInstance = NewCooldown;
    }
}

void UGGFGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    // 어빌리티가 종료되는 경우 어빌리티 입력을 초기화합니다.
    GetCurrentAbilitySpec()->InputPressed = false;
}

bool UGGFGameplayAbility::InternalCanActivate()
{
#if WITH_EDITOR
      // TODO 원인 분석 및 수정 필요
    /**
     * CanActivateAbility에 이미 포함되어 있음에도 불구하고 showdebug abilitysystem 콘솔 창에서 쿨다운으로 인한 비활성화 표시가 되지 않습니다.
     * 일단 디버깅 편의성을 위해 임시로 이곳에 한 번 더 검사를 진행하도록 설정해두었습니다.
     */
    return CheckCooldown(CurrentSpecHandle, CurrentActorInfo);
#endif

    return true;
}
