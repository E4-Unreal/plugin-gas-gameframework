// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GGFAT_DetectInteractableActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableActorDetected, AActor*, InteractableActor);

// TODO DetectTarget처럼 좀 더 범용적인 어빌리티 태스크로 전환?
/**
 * 상호작용 가능한 오브젝트 감지를 위한 어빌리티 태스크
 */
UCLASS()
class GGFINTERACTIONSYSTEM_API UGGFAT_DetectInteractableActor : public UAbilityTask
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnInteractableActorDetected OnInteractableActorDetected;

protected:
    float MaxDistance;
    float SphereRadius;

#if WITH_EDITORONLY_DATA
    bool bShowDebug;
#endif

public:
    UGGFAT_DetectInteractableActor();

    UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (DisplayName="DetectInteractableActor",
        HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
    static UGGFAT_DetectInteractableActor* CreateTask(UGameplayAbility* OwningAbility, bool ShowDebug = false, float InMaxDistance = 1000, float InSphereRadius = 20);

    virtual void TickTask(float DeltaTime) override;

protected:
    virtual void Scan(float DeltaTime);
};
