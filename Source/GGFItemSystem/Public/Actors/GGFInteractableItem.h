// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GGFInteractableActor.h"
#include "GGFInteractableItem.generated.h"

class UGGFItemDataManager;

/**
 * 레벨에 존재하는 상호작용 가능한 아이템입니다.
 */
UCLASS()
class GGFITEMSYSTEM_API AGGFInteractableItem : public AGGFInteractableActor
{
    GENERATED_BODY()

    // 아이템 데이터 서브 시스템을 사용하기 위한 전용 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetItemDataManager, Category = "Component")
    TObjectPtr<UGGFItemDataManager> ItemDataManager;

protected:
    // 보유 아이템 수량
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetAmount, BlueprintSetter = SetAmount, Category = "State", Transient, ReplicatedUsing = OnRep_Amount)
    int32 Amount;

public:
    AGGFInteractableItem();

    /* AActor */

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PreInitializeComponents() override;
    virtual void OnConstruction(const FTransform& Transform) override;

protected:
    /* 이벤트 */

    UFUNCTION(BlueprintCallable)
    virtual void OnIDUpdated(int32 NewID);

    UFUNCTION(BlueprintCallable)
    virtual void UpdateDisplayName();

protected:
    /* 리플리케이트 */

    UFUNCTION()
    virtual void OnRep_Amount(int32 OldAmount);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFItemDataManager* GetItemDataManager() const { return ItemDataManager; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetAmount() const { return Amount; }

    /* Setter */

    UFUNCTION(BlueprintSetter)
    virtual void SetAmount(int32 NewAmount);
};
