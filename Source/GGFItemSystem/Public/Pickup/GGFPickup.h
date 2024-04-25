// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFItemDefinition.h"
#include "GameFramework/Actor.h"
#include "GGFPickup.generated.h"

class UWidgetComponent;
class UBoxComponent;
class UGGFItemConfig_Pickup;
struct FGGFPickupData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdatedSignature);

/**
 * 상호작용을 통해 습득할 수 있는 아이템 액터 클래스입니다.
 * 스폰 시스템에서 아이템을 스폰할 때 사용되며, 아이템 스폰 후 InitFromItemDefinition 혹은 InitFromItemConfig를 명시적으로 호출해주어야 합니다.
 */
UCLASS()
class GGFITEMSYSTEM_API AGGFPickup : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnUpdatedSignature OnUpdated;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetItemDefinition, Category = "State", Transient)
    TObjectPtr<UGGFItemDefinition> ItemDefinition;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UGGFItemConfig_Pickup> ItemConfig;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetAmount, BlueprintSetter = SetAmount, Category = "State", Transient)
    int32 Amount;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    bool bIsInitialized;

private:
    UPROPERTY(VisibleAnywhere, BlueprintGetter = "GetDisplayMesh", Category = "Component")
    TObjectPtr<UStaticMeshComponent> DisplayMesh;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = "GetWidget", Category = "Component")
    TObjectPtr<UWidgetComponent> Widget;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = "GetTriggerBox", Category = "Component")
    TObjectPtr<UBoxComponent> TriggerBox;

public:
    AGGFPickup(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */
    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

    /* API */
    UFUNCTION(BlueprintCallable)
    virtual void InitFromItemDefinition(UGGFItemDefinition* InItemDefinition);

    UFUNCTION(BlueprintCallable)
    virtual void InitFromItemConfig(UGGFItemConfig_Pickup* InItemConfig);

    UFUNCTION(BlueprintCallable)
    virtual void InitFromPickupData(const FGGFPickupData& InPickupData);

    virtual void Reset() override;

protected:
    // 아이템을 적절한 위치에 배치
    UFUNCTION(BlueprintCallable)
    virtual void SetLandingPosition();

    // 위젯을 표시하거나 숨깁니다.
    UFUNCTION(BlueprintCallable)
    virtual void SetWidgetVisibility(bool bEnable);

    // 외곽선을 표시하거나 숨깁니다.
    UFUNCTION(BlueprintCallable)
    virtual void SetOutlineVisibility(bool bEnable);

public:
    UFUNCTION(BlueprintGetter)
    FORCEINLINE UStaticMeshComponent* GetDisplayMesh() const { return DisplayMesh; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UWidgetComponent* GetWidget() const { return Widget; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UBoxComponent* GetTriggerBox() const { return TriggerBox; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFItemDefinition* GetItemDefinition() const { return ItemDefinition; }

    UFUNCTION(BlueprintGetter)
    virtual FORCEINLINE int32 GetAmount() const { return Amount; }

    UFUNCTION(BlueprintSetter)
    virtual void SetAmount(int32 InAmount);

    UFUNCTION(BlueprintPure)
    virtual FORCEINLINE FText GetDisplayNameText() const { return ItemDefinition ? ItemDefinition->GetDisplayName() : FText::GetEmpty(); }
};
