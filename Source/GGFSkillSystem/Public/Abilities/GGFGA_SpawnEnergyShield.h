// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGA_Montage.h"
#include "GGFGA_SpawnEnergyShield.generated.h"

/**
 * 자신의 주위에 에너지 실드를 스폰하는 스킬 전용 어빌리티 클래스입니다.
 */
UCLASS()
class GGFSKILLSYSTEM_API UGGFGA_SpawnEnergyShield : public UGGFGA_Montage
{
    GENERATED_BODY()

public:
    // 스폰 타이밍 설정 전용 애님 몽타주 노티파이 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Animation")
    FName SpawnNotifyName = "Spawn";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<AActor> EnergyShieldClass;

    // 생성된 에너지 실드가 지속되는 시간 (초)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float EnergyShieldLifeTime = 10;

protected:
    TWeakObjectPtr<AActor> SpawnedEnergyShield = nullptr;

    bool bEnergyShieldSpawned = false;

public:
    UGGFGA_SpawnEnergyShield();

    /* GameplayAbility */

    virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData) override;

protected:
    /* GGFGA_Montage */

    virtual void OnPlayMontageNotifyBegin_Implementation(FName NotifyName) override;
    virtual void OnMontageCompleted_Implementation() override;

    /* 메서드 */
    UFUNCTION(BlueprintCallable)
    virtual void SpawnEnergyShield();
};
