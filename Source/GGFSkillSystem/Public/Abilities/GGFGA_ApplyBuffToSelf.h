// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueInterface.h"
#include "Abilities/GGFGA_Montage.h"
#include "GGFGA_ApplyBuffToSelf.generated.h"

/**
 * 기본적인 버프 스킬 전용 어빌리티 클래스입니다.
 */
UCLASS()
class GGFSKILLSYSTEM_API UGGFGA_ApplyBuffToSelf : public UGGFGA_Montage
{
    GENERATED_BODY()

public:
    // 자신에게 적용할 버프 전용 게임플레이 이펙트 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UGameplayEffect> BuffClass;

    // 자신에게 버프를 적용할 타이밍을 적용할 노티파이 이름
    // 만약 대응하는 노티파이 이름이 없는 경우 몽타주 재생이 완료될 때 적용됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName BuffNotifyName = "Buff";

    // true 인 경우 스킬 발동 즉시 버프가 적용됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bApplyImmediately = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGameplayCueTag BuffCueTag;

protected:
    bool bApplied = false;

public:
    /* GameplayAbility */

    virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData) override;
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void OnPlayMontageNotifyBegin_Implementation(FName NotifyName) override;
    virtual void OnMontageCompleted_Implementation() override;

    /* GEGameplayAbility */

    virtual bool InternalCanActivate() override;

protected:
    /* 메서드 */

    virtual void ApplyBuffToSelf();
};
