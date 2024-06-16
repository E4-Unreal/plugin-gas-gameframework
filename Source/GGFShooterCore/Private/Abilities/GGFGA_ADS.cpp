// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFGA_ADS.h"

#include "GGFShooterGameplayTags.h"
#include "Components/GGFCameraComponent.h"
#include "Weapons/GGFSniper.h"

UGGFGA_ADS::UGGFGA_ADS()
{
    // 입력 태그 설정
    InputTag = Input::ADS;

    // 어빌리티 태그 설정
    AbilityTags.AddLeafTag(State::ADS);
    ActivationOwnedTags.AddLeafTag(State::ADS);
}

void UGGFGA_ADS::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

    CameraComponent = ActorInfo->AvatarActor->GetComponentByClass<UGGFCameraComponent>();
    bValid = bValid && CameraComponent.IsValid();
}

void UGGFGA_ADS::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // 무기 FOV로 설정
    float WeaponFOV = GetCameraComponent()->GetDefaultFOV() / GetFireArm()->GetCameraMultiplier();
    GetCameraComponent()->SetFieldOfView(WeaponFOV);

    // 저격총의 경우 스코프 UI 표시
    if(auto Sniper = Cast<AGGFSniper>(GetFireArm()))
    {
        Sniper->ShowScopeWidget(true);
    }
}

void UGGFGA_ADS::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    // 저격총의 경우 스코프 UI 숨기기
    if(auto Sniper = Cast<AGGFSniper>(GetFireArm()))
    {
        Sniper->ShowScopeWidget(false);
    }

    // 기본 FOV로 복원
    GetCameraComponent()->SetFieldOfView(-1);

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UGGFGA_ADS::InternalCanActivate()
{
    return Super::InternalCanActivate() && !GetFireArm()->IsEquipping();
}
