// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GGFEffectManager.h"
#include "GGFActivatableComponent.generated.h"

/**
 * 활성화 상태
 */
UENUM(BlueprintType)
enum class EGGFActivationState : uint8
{
    Init,
    Activating,
    Activated,
    Deactivating,
    Deactivated
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBeginActivateSignature, AActor*, Causer, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEndActivateSignature, AActor*, Causer, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbortActivateSignature, AActor*, Causer, AActor*, Instigator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBeginDeactivateSignature, AActor*, Causer, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEndDeactivateSignature, AActor*, Causer, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbortDeactivateSignature, AActor*, Causer, AActor*, Instigator);

class USoundCue;

// TODO 리팩토링 (구조체 활용?)
/**
 * 활성화 및 비활성화 전용 컴포넌트
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFGIMMICKSYSTEM_API UGGFActivatableComponent : public UGGFActorComponent
{
    GENERATED_BODY()

public:
    /* 델리게이트 */

    // 활성화 시작
    UPROPERTY(BlueprintAssignable)
    FOnBeginActivateSignature OnActivationBegin;

    // 활성화 종료
    UPROPERTY(BlueprintAssignable)
    FOnEndActivateSignature OnActivationEnd;

    // 활성화 취소
    UPROPERTY(BlueprintAssignable)
    FOnBeginActivateSignature OnActivationAbort;

    // 비활성화 시작
    UPROPERTY(BlueprintAssignable)
    FOnBeginDeactivateSignature OnDeactivationBegin;

    // 비활성화 종료
    UPROPERTY(BlueprintAssignable)
    FOnEndActivateSignature OnDeactivationEnd;

    // 비활성화 취소
    UPROPERTY(BlueprintAssignable)
    FOnEndActivateSignature OnDeactivationAbort;

public:
    // 활성화 혹은 비활성화 취소 가능 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bCanAbort = false;

    // 활성화 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float ActivationDuration = 0;

    // 비활성화 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float DeactivationDuration = 0;

    // 활성화 시 사용할 이펙트
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGGFEffectDefinitionContainer ActivationEffect;

    // 비활성화 시 사용할 이펙트
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGGFEffectDefinitionContainer DeactivationEffect;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    EGGFActivationState ActivationState;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<AActor> Causer;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<AActor> Instigator;

    FTimerHandle ActivationTimer;
    FTimerHandle DeactivationTimer;

public:
    /* ActorComponent */

    virtual void BeginDestroy() override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual bool TryActivate(AActor* InCauser, AActor* InInstigator);

    UFUNCTION(BlueprintCallable)
    virtual bool TryDeactivate(AActor* InCauser, AActor* InInstigator);

protected:
    /* 이벤트 */

    UFUNCTION()
    virtual void InternalOnActivationEnd();

    UFUNCTION()
    virtual void InternalOnDeactivationEnd();
};
