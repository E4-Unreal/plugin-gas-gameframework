// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGA_Montage.h"
#include "GGFGA_SpawnActor.generated.h"

/**
 * 자신의 위치에 특정 액터를 스폰하는 어빌리티 클래스입니다.
 */
UCLASS()
class GGFSKILLSYSTEM_API UGGFGA_SpawnActor : public UGGFGA_Montage
{
    GENERATED_BODY()

public:
    // 스폰 타이밍 설정 전용 애님 몽타주 노티파이 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Animation")
    FName SpawnNotifyName = "Spawn";

    // 스폰할 액터 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<AActor> ActorToSpawn;

    // 스폰된 액터 수명
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float SpawnedActorLifeTime = 10;

protected:
    TWeakObjectPtr<AActor> SpawnedActor = nullptr;

    bool bActorSpawned = false;

public:
    /* GameplayAbility */

    virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData) override;

protected:
    /* GGFGA_Montage */

    virtual void OnPlayMontageNotifyBegin_Implementation(FName NotifyName) override;
    virtual void OnMontageCompleted_Implementation() override;

    /* 메서드 */
    UFUNCTION(BlueprintCallable)
    virtual void SpawnActor();
};
