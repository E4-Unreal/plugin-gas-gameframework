// Fill out your copyright notice in the Description page of Project Settings.


#include "GGFInventoryManagerBase.h"

#include "GGFInventoryItemConfig.h"
#include "Net/UnrealNetwork.h"

bool FGGFInventoryItem::IsValid() const
{
    return ItemDefinition && InventoryItemConfig && Amount > 0;
}

const FInventoryItemData& FGGFInventoryItem::GetInventoryData() const
{
    return InventoryItemConfig->GetInventoryData();
}

int32 FGGFInventoryItem::GetFreeAmount() const
{
    return GetInventoryData().MaxStack - Amount;
}

UGGFInventoryManagerBase::UGGFInventoryManagerBase()
{
    SetIsReplicatedByDefault(true);
}

void UGGFInventoryManagerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, MaxSlotNum);
    DOREPLIFETIME(ThisClass, Inventory);
}

bool UGGFInventoryManagerBase::AddItem(const FGGFInventoryItem& Item)
{
    // 서버에서만 호출 가능
    if(!GetOwner()->HasAuthority()) return false;

    // 아이템 유효성 검사
    if(Item.IsNotValid()) return false;

    // 지역 변수 선언
    int32 NewAmount = Item.Amount;

    // 기존 아이템 슬롯에 먼저 추가
    const TArray<int32> SortedSlotIndices = SearchItem(Item.ItemDefinition);
    for (int32 SlotIndex : SortedSlotIndices)
    {
        // 인벤토리 아이템 참조 변수 선언
        FGGFInventoryItem& InventoryItem = GetInventoryItem(SlotIndex);

        // 기존 아이템 슬롯에 수량 채워넣기
        int32 FreeAmount = InventoryItem.GetFreeAmount();
        int32 AmountToAdd = FMath::Min(FreeAmount, NewAmount);
        InventoryItem.Amount += AmountToAdd;
        NewAmount -= AmountToAdd;

        // 아이템 수량이 소진된 경우 조기 종료
        if(NewAmount <= 0) break;
    }

    // 기존 아이템에 단 1개라도 추가된 경우 결과를 true로 설정
    bool bResult = NewAmount != Item.Amount;

    // 아이템 수량이 남은 경우 빈 슬롯에 아이템 추가
    if(NewAmount > 0 && AddItemToEmptySlot(FGGFInventoryItem(Item.ItemDefinition, Item.InventoryItemConfig, NewAmount))) bResult = true;

    // 인벤토리에 아이템이 추가된 경우
    if(bResult)
    {
        // UI 업데이트
        OnInventoryUpdated.Broadcast(Inventory.Slots);

        // 인벤토리 업데이트
        SetInventoryDirty();
    }

    return bResult;
}

bool UGGFInventoryManagerBase::RemoveItem(const FGGFInventoryItem& Item)
{
    // 지역 변수 선언
    int32 AmountToRemove = Item.Amount;

    // 아이템 수량 검색
    const TArray<int32> SortedSlotIndices = SearchItem(Item.ItemDefinition);
    int32 AvailableItemAmount = 0;
    for(int32 SlotIndex : SortedSlotIndices)
    {
        // 인벤토리 아이템 참조 변수 선언
        FGGFInventoryItem& InventoryItem = GetInventoryItem(SlotIndex);

        // 아이템 수량 계산
        AvailableItemAmount += InventoryItem.Amount;
        if(AvailableItemAmount >= Item.Amount) break;
    }

    // 아이템 수량이 부족한 경우
    if(AvailableItemAmount < Item.Amount) return false;

    // 슬롯 인덱스 내림차순으로 아이템 제거
    for(int i = SortedSlotIndices.Num() - 1; i >= 0; i--)
    {
        // 인벤토리 슬롯 인덱스 변수 선언
        int32 SlotIndex = SortedSlotIndices[i];

        // 인벤토리 아이템 참조 변수 선언
        FGGFInventoryItem& InventoryItem = GetInventoryItem(SlotIndex);

        // 아이템 제거
        if(AmountToRemove < InventoryItem.Amount)
        {
            // 인벤토리 슬롯에 들어있는 아이템 수량이 충분한 경우
            InventoryItem.Amount -= AmountToRemove;
            break;
        }
        else
        {
            // 인벤토리 슬롯에 들어있는 아이템 수량이 부족한 경우
            AmountToRemove -= InventoryItem.Amount;
            Inventory.Slots.RemoveSwap(FGGFInventorySlot(SlotIndex, InventoryItem));
            InventoryMap.Remove(SlotIndex);

            // 인벤토리 슬롯에 들어있는 아이템 수량이 동일한 경우
            if(AmountToRemove <= 0) break;
        }
    }

    // 인벤토리 업데이트
    SetInventoryDirty();

    return true;
}

bool UGGFInventoryManagerBase::AddItemToEmptySlot(const FGGFInventoryItem& Item)
{
    // 인벤토리 빈 슬롯이 존재하는지 확인
    if(IsFull()) return false;

    // 빈 슬롯 인덱스 유효성 검사
    int32 EmptySlotIndex = GetEmptySlotIndex();
    if(EmptySlotIndex < 0) return false;

    // 빈 슬롯에 아이템 추가
    int32 ArrayIndex = Inventory.Slots.Emplace(EmptySlotIndex, Item);
    InventoryMap.Emplace(EmptySlotIndex, &Inventory.Slots[ArrayIndex].Item);

    // 아이템 추가 성공
    return true;
}

void UGGFInventoryManagerBase::CachingInventory()
{
    // 인벤토리 맵 초기화
    InventoryMap.Empty(Inventory.Slots.Num());

    // 인벤토리 맵 캐싱
    for (auto& [Index, Item] : Inventory.Slots)
    {
        InventoryMap.Emplace(Index, &Item);
    }
}

int32 UGGFInventoryManagerBase::GetEmptySlotIndex() const
{
    for (int32 index = 0; index < MaxSlotNum; index++)
    {
        if(!InventoryMap.Contains(index)) return index;
    }

    return -1;
}

TArray<int32> UGGFInventoryManagerBase::SearchItem(UDataAsset* Item) const
{
    // 배열 선언
    TArray<int32> SortedSlotIndices;

    // 아이템 유효성 검사
    if(Item == nullptr) return SortedSlotIndices;

    // 메모리 할당
    SortedSlotIndices.Reserve(InventoryMap.Num());

    // 동일한 아이템 검색
    for(const auto& Slot : Inventory.Slots)
    {
        // 동일한 아이템이 들어있는 슬롯 인덱스 저장
        if(Slot == Item) SortedSlotIndices.Emplace(Slot.Index);
    }

    // 일반적으로 가장 작은 인덱스의 아이템부터 채우거나 사용하기 때문에 정렬해줍니다.
    SortedSlotIndices.Sort();

    return SortedSlotIndices;
}

void UGGFInventoryManagerBase::SetInventoryDirty()
{
    // 서버에서만 호출 가능
    if(!GetOwner()->HasAuthority()) return;

    // 서버 시간 기록
    if(UWorld* World = GetWorld())
    {
        float CurrentServerTime = World->TimeSeconds;
        Inventory.LastModifiedTime = CurrentServerTime;
    }
}

void UGGFInventoryManagerBase::OnRep_MaxSlotNum(int32 OldMaxSlotNum)
{
    // TODO
}

void UGGFInventoryManagerBase::OnRep_Inventory(const FGGFInventory& OldInventory)
{
    // 네트워크 이슈로 인해 오래된 데이터로 업데이트된 경우 복원 진행
    if(OldInventory.LastModifiedTime > Inventory.LastModifiedTime)
    {
        Inventory = OldInventory;
        return;
    }

    // 인벤토리 캐싱
    CachingInventory();

    // UI 업데이트
    OnInventoryUpdated.Broadcast(Inventory.Slots);
}
