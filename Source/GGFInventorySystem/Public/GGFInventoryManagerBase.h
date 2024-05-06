// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGFInventoryManagerBase.generated.h"

class UGGFInventoryItemConfig;
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
    TObjectPtr<UDataAsset> ItemDefinition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UGGFInventoryItemConfig> InventoryItemConfig;

    // 아이템 수량
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 Amount;

public:
    bool IsValid() const;
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

    const FInventoryItemData& GetInventoryData() const;

    int32 GetMaxStack() const;

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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 Index;

    // 인벤토리 아이템 정보
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
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

    FORCEINLINE bool operator==(const UDataAsset* OtherItemDefinition) const
    {
        return Item.ItemDefinition == OtherItemDefinition;
    }

    FORCEINLINE bool operator!=(const UDataAsset* OtherItemDefinition) const
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

    // 인벤토리 슬롯 인덱스와 실제 배열 인덱스 매핑 정보
    // TMap<SlotIndex, ArrayIndex>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<int32, int32> InventoryIndexMap;

    // 아이템 별 수량 통계
    // TMap<ItemDefinition, Amount>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<TObjectPtr<UDataAsset>, int32> ItemAmountMap;

public:
    UGGFInventoryManagerBase();

    /* ActorComponent */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    /* API */
    // 인벤토리에 아이템을 추가합니다. (서버 전용)
    UFUNCTION(BlueprintCallable, Category = "ServerOnly")
    virtual bool AddItem(const FGGFInventoryItem& Item, int32& Remainder);

    // 인벤토리에서 아이템을 제거합니다. (서버 전용)
    UFUNCTION(BlueprintCallable, Category = "ServerOnly")
    virtual bool RemoveItem(const FGGFInventoryItem& Item);

    // 인벤토리 슬롯을 교환합니다.
    UFUNCTION(BlueprintCallable, Category = "ServerOnly")
    virtual bool SwapInventorySlots(const int32 SourceSlotIndex, const int32 TargetSlotIndex);

    /* 쿼리 */
    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsFull() const { return InventoryIndexMap.Num() >= MaxSlotNum; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE int32 GetItemAmount(UDataAsset* ItemDefinition) const { return ItemAmountMap.Contains(ItemDefinition) ? ItemAmountMap[ItemDefinition] : 0; }

    // 주어진 인벤토리 슬롯 인덱스에 대응하는 인벤토리 슬롯 반환 (읽기 전용)
    UFUNCTION(BlueprintPure)
    virtual const FORCEINLINE FGGFInventorySlot& GetInventorySlot(int32 SlotIndex) const { return Inventory.Slots[InventoryIndexMap[SlotIndex]]; }

    // 주어진 인벤토리 슬롯 인덱스에 대응하는 인벤토리 아이템 반환 (읽기 전용)
    UFUNCTION(BlueprintPure)
    virtual const FORCEINLINE FGGFInventoryItem& GetInventoryItem(int32 SlotIndex) const { return GetInventorySlot(SlotIndex).Item; }

protected:
    // 인벤토리 및 캐시에 아이템 등록
    virtual void RegisterInventoryItemToSlot(const FGGFInventoryItem& Item, int32 SlotIndex);

    // 인벤토리 및 캐시에서 아이템 등록 해제
    virtual void UnregisterInventoryItemFromSlot(int32 SlotIndex);

    // 인벤토리 캐싱
    virtual void CachingInventory();

    // 빈 슬롯에 아이템 추가
    virtual bool AddItemToEmptySlot(const FGGFInventoryItem& Item, int32& Remainder);

    // 아이템 수량 통계 갱신
    virtual void UpdateItemAmount(UDataAsset* ItemDefinition, int32 InAmount);

    /* 쿼리 */
    // 비어있는 인벤토리 슬롯 중 가장 작은 인덱스 구하기
    virtual int32 GetEmptySlotIndex() const;

    /**
     * 동일한 아이템이 들어있는 슬롯 인덱스 목록 구하기
     * @return 오름차순으로 정렬된 슬롯 인덱스 목록
     */
    virtual TArray<int32> SearchItem(UDataAsset* ItemDefinition) const;

    // 인벤토리 수정 여부 설정 (마지막으로 수정된 서버 시간 기록)
    virtual void SetInventoryDirty();

    // 주어진 인벤토리 슬롯 인덱스에 대응하는 인벤토리 아이템을 참조 타입으로 반환
    FORCEINLINE virtual FGGFInventorySlot& GetInventorySlotReference(int32 SlotIndex) { return Inventory.Slots[InventoryIndexMap[SlotIndex]]; }

    // 주어진 인벤토리 슬롯 인덱스에 대응하는 인벤토리 아이템을 참조 타입으로 반환
    FORCEINLINE virtual FGGFInventoryItem& GetInventoryItemReference(int32 SlotIndex) { return GetInventorySlotReference(SlotIndex).Item; }

protected:
    /* 리플리케이트 */
    UFUNCTION()
    virtual void OnRep_MaxSlotNum(int32 OldMaxSlotNum);

    UFUNCTION()
    virtual void OnRep_Inventory(const FGGFInventory& OldInventory);
};
