// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFItemDefinition.h"
#include "Components/ActorComponent.h"
#include "GGFInventoryManagerBase.generated.h"

class UGGFItemDefinition;
struct FInventoryItemData;

/**
 * 인벤토리 아이템 정보
 */
USTRUCT(BlueprintType)
struct FGGFInventoryItem
{
    GENERATED_BODY()

public:
    // 아이템 정보
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UGGFItemDefinition> ItemDefinition;

    // 아이템 수량
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 Amount;

public:
    bool IsValid() const;
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

    const FInventoryItemData& GetInventoryData() const;

    // MaxStack - Amount
    int32 GetFreeAmount() const;
};

/**
 * 인벤토리 슬롯 정보
 */
USTRUCT(BlueprintType)
struct FGGFInventorySlot
{
    GENERATED_BODY()

    // 인벤토리 슬롯 인덱스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
    int32 Index;

    // 인벤토리 아이템 정보
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGGFInventoryItem Item;

    bool IsValid() const { return Index >= 0 && Item.IsValid(); }
    bool IsNotValid() const { return !IsValid(); }

    FORCEINLINE friend uint32 GetTypeHash(const FGGFInventorySlot& InventorySlot)
    {
        return GetTypeHash(InventorySlot.Index);
    }

    FORCEINLINE bool operator==(const FGGFInventorySlot& Other) const
    {
        return Index == Other.Index;
    }

    FORCEINLINE bool operator!=(const FGGFInventorySlot& Other) const
    {
        return !(*this == Other);
    }

    FORCEINLINE bool operator==(const UGGFItemDefinition* OtherItemDefinition) const
    {
        return Item.ItemDefinition == OtherItemDefinition;
    }

    FORCEINLINE bool operator!=(const UGGFItemDefinition* OtherItemDefinition) const
    {
        return !(*this == OtherItemDefinition);
    }

    FORCEINLINE bool operator==(const int32 OtherIndex) const
    {
        return Index == OtherIndex;
    }

    FORCEINLINE bool operator!=(const int32 OtherIndex) const
    {
        return !(*this == OtherIndex);
    }
};

/**
 * 리플리케이트 전용 인벤토리 구조체
 */
USTRUCT(BlueprintType)
struct FGGFInventory
{
    GENERATED_BODY()

    // 서버에서 마지막으로 수정된 시간을 기록함으로써 리플리케이트 순서를 식별하기 위한 변수입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LastModifiedTime;

    // 인벤토리 슬롯 목록
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FGGFInventorySlot> Slots;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryUpdatedSignature, const TArray<FGGFInventorySlot>&, InventorySlots);

/**
 * 인벤토리 코어 기능만 구현된 클래스
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFINVENTORYSYSTEM_API UGGFInventoryManagerBase : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FInventoryUpdatedSignature OnInventoryUpdated;

protected:
    // 최대 인벤토리 슬롯 수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", ReplicatedUsing = OnRep_MaxSlotNum, meta = (ClampMin = 0))
    int32 MaxSlotNum;

    // 실제 인벤토리 아이템 정보들이 저장되어 있습니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, ReplicatedUsing = OnRep_Inventory)
    FGGFInventory Inventory;

    // TMap<Index, InventoryItem>
    TMap<int32, FGGFInventoryItem*> InventoryMap;

public:
    UGGFInventoryManagerBase();

    /* ActorComponent */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    /* API */
    // 인벤토리에 아이템을 추가합니다. (서버 전용)
    UFUNCTION(BlueprintCallable, Category = "ServerOnly")
    virtual bool AddItem(const FGGFInventoryItem& Item);

    /* 쿼리 */
    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsFull() const { return InventoryMap.Num() >= MaxSlotNum; }

protected:
    // 인벤토리 캐싱
    virtual void CachingInventory();

    // 빈 슬롯에 아이템 추가
    virtual bool AddItemToEmptySlot(const FGGFInventoryItem& Item);

    /* 쿼리 */
    // 비어있는 인벤토리 슬롯 중 가장 작은 인덱스 구하기
    virtual int32 GetEmptySlotIndex() const;

    // 동일한 아이템이 들어있는 슬롯 인덱스 목록 구하기
    virtual TArray<int32> SearchItem(UGGFItemDefinition* Item) const;

    // 인벤토리 수정 여부 설정 (마지막으로 수정된 서버 시간 기록)
    virtual void SetInventoryDirty();

protected:
    /* 리플리케이트 */
    UFUNCTION()
    virtual void OnRep_MaxSlotNum(int32 OldMaxSlotNum);

    UFUNCTION()
    virtual void OnRep_Inventory(const FGGFInventory& OldInventory);
};
