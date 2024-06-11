// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "GGFActivatableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginActivateSignature, AActor*, Activator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndActivateSignature, AActor*, Activator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbortActivateSignature, AActor*, Activator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginDeactivateSignature, AActor*, Activator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndDeactivateSignature, AActor*, Activator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbortDeactivateSignature, AActor*, Activator);

class USoundCue;

// TODO 리팩토링 (구조체 활용?)
/**
 * 활성화 및 비활성화 전용 컴포넌트
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFGIMMICKSYSTEM_API UGGFActivatableComponent : public UAudioComponent
{
    GENERATED_BODY()

public:
    /* 델리게이트 */

    // 활성화 시작
    UPROPERTY(BlueprintAssignable)
    FOnBeginActivateSignature OnBeginActivate;

    // 활성화 종료
    UPROPERTY(BlueprintAssignable)
    FOnEndActivateSignature OnEndActivate;

    // 활성화 취소
    UPROPERTY(BlueprintAssignable)
    FOnBeginActivateSignature OnAbortActivate;

    // 비활성화 시작
    UPROPERTY(BlueprintAssignable)
    FOnBeginDeactivateSignature OnBeginDeactivate;

    // 비활성화 종료
    UPROPERTY(BlueprintAssignable)
    FOnEndActivateSignature OnEndDeactivate;

    // 비활성화 취소
    UPROPERTY(BlueprintAssignable)
    FOnEndActivateSignature OnAbortDeactivate;

public:
    // 활성화 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float ActivationDuration = 0;

    // 비활성화 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float DeactivationDuration = 0;

    // 활성화 시 사용할 사운드
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TObjectPtr<USoundCue> ActivationSound;

    // 비활성화 시 사용할 사운드
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TObjectPtr<USoundCue> DeactivationSound;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    bool bActivated;

    FTimerHandle ActivationTimerHandle;
    FTimerHandle DeactivationTimerHandle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<AActor> Activator;

public:
    UGGFActivatableComponent();

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual bool TryActivate(AActor* NewActivator, bool bForce = false);

    UFUNCTION(BlueprintCallable)
    virtual bool TryDeactivate(AActor* NewActivator, bool bForce = false);

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsActivated() const { return bActivated; }

protected:
    /* 메서드 */

    UFUNCTION(BlueprintCallable)
    virtual void PlaySound(USoundCue* NewSound, float Duration);

    UFUNCTION(BlueprintCallable)
    virtual void ResetTimer();

    /* 이벤트 */

    UFUNCTION(BlueprintCallable)
    virtual void InternalOnEndActivate();

    UFUNCTION(BlueprintCallable)
    virtual void InternalOnEndDeactivate();
};
