// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GGFTriggerBox.h"
#include "Components/GGFEffectManager.h"
#include "Interfaces/GGFActivatableInterface.h"
#include "GGFTriggerPad.generated.h"

class UGGFTriggerComponent;

/**
 * 특정 액터가 오버랩되면 트리거를 동작시키는 패드입니다.
 */
UCLASS()
class GGFGIMMICKSYSTEM_API AGGFTriggerPad : public AGGFTriggerBox, public IGGFActivatableInterface
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetTriggerComponent, Category = "Component")
    TObjectPtr<UGGFTriggerComponent> TriggerComponent;

protected:
    // 트리거를 발동하기 위한 조건으로 특정 액터가 특정 개수만큼 오버랩되어야 합니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 1))
    TMap<TSubclassOf<AActor>, int32> TriggerConditionMap;

    // 활성화 이펙트
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGGFEffectDefinitionContainer ActivateEffect;

    // 비활성화 이펙트
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGGFEffectDefinitionContainer DeactivateEffect;

public:
    AGGFTriggerPad();

    /* ActivationInterface */

    virtual bool TryActivate_Implementation(AActor* InCauser, AActor* InInstigator) override;
    virtual bool TryDeactivate_Implementation(AActor* InCauser, AActor* InInstigator) override;

protected:
    /* TriggerBox */

    virtual void OnCollisionBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
    virtual void OnCollisionEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

    /* 메서드 */

    // 트리거 조건 만족 여부에 따라 활성화 혹은 비활성화
    UFUNCTION(BlueprintCallable)
    virtual void CheckTriggerCondition();

    // 트리거 조건 확인
    UFUNCTION(BlueprintPure)
    virtual bool IsTriggerConditionSatisfied();

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFTriggerComponent* GetTriggerComponent() const { return TriggerComponent; }
};
