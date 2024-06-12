// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GGFActorComponent.h"
#include "GGFItemDataManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIDUpdated, int32, NewID);

struct FGGFItemData;
class UGGFItemDefinition;

/**
 * 아이템 데이터 서브 시스템을 사용하기 위한 전용 컴포넌트입니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFITEMSYSTEM_API UGGFItemDataManager : public UGGFActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnIDUpdated OnIDUpdated;

protected:
    // 아이템 ID
    UPROPERTY(EditAnywhere, BlueprintGetter = GetID, BlueprintSetter = SetID, Category = "Config")
    int32 ID;

    // 아이템 ID에 대응하는 데이터 에셋
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDefinition, Category = "State", Transient)
    TObjectPtr<UGGFItemDefinition> Definition;

public:
    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintPure)
    FGGFItemData GetData() const;

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetID() const { return ID; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFItemDefinition* GetDefinition() const { return Definition; }

    /* Setter */

    UFUNCTION(BlueprintSetter)
    virtual void SetID(int32 NewID);
};
