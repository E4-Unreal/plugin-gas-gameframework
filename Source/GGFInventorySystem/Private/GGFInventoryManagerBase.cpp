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

int32 FGGFInventoryItem::GetMaxStack() const
{
    return GetInventoryData().MaxStack;
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

bool UGGFInventoryManagerBase::AddItem(const FGGFInventoryItem& Item, int32& Remainder)
{
    // 변수 초기화
    Remainder = Item.Amount;

    // 서버에서만 호출 가능
    if(!GetOwner()->HasAuthority()) return false;

    // 아이템 유효성 검사
    if(Item.IsNotValid()) return false;

    // 기존 아이템 슬롯에 먼저 추가
    const TArray<int32> SortedSlotIndices = SearchItem(Item.ItemDefinition);
    for (int32 SlotIndex : SortedSlotIndices)
    {
        // 기존 인벤토리 아이템 가져오기
        FGGFInventoryItem& ExistingInventoryItem = GetInventoryItemReference(SlotIndex);

        // 기존 인벤토리 아이템에 수량 채워넣기
        int32 FreeAmount = ExistingInventoryItem.GetFreeAmount();
        int32 AmountToAdd = FMath::Min(FreeAmount, Remainder);
        ExistingInventoryItem.Amount += AmountToAdd;
        Remainder -= AmountToAdd;

        // 아이템 수량이 소진된 경우 조기 종료
        if(Remainder <= 0) break;
    }

    // 아이템 수량이 남은 경우 빈 슬롯에 아이템 추가
    while(Remainder > 0 && AddItemToEmptySlot(FGGFInventoryItem(Item.ItemDefinition, Item.InventoryItemConfig, Remainder), Remainder))
    {
        // 모든 아이템 수량이 소진되거나 빈 슬롯이 존재하지 않을 때까지 반복
    }

    // 단 1개라도 인벤토리에 아이템이 추가된 경우 true 설정
    bool bResult = Remainder != Item.Amount;

    // 인벤토리에 아이템이 추가된 경우
    if(bResult)
    {
        // UI 업데이트
        OnInventoryUpdated.Broadcast(Inventory.Slots);

        // 인벤토리 업데이트
        SetInventoryDirty();

        // 아이템 수량 통계 업데이트
        UpdateItemAmount(Item.ItemDefinition, Item.Amount - Remainder);
    }

    return bResult;
}

bool UGGFInventoryManagerBase::RemoveItem(const FGGFInventoryItem& Item)
{
    // 서버에서만 호출 가능
    if(!GetOwner()->HasAuthority()) return false;

    // 지역 변수 선언
    int32 AmountToRemove = Item.Amount;

    // 아이템 수량이 부족한 경우
    if(GetItemAmount(Item.ItemDefinition) < Item.Amount) return false;

    // 슬롯 인덱스 내림차순으로 아이템 제거
    const TArray<int32> SortedSlotIndices = SearchItem(Item.ItemDefinition);
    for(int i = SortedSlotIndices.Num() - 1; i >= 0; i--)
    {
        // 인벤토리 슬롯 인덱스 변수 선언
        int32 SlotIndex = SortedSlotIndices[i];

        // 인벤토리 아이템 참조 변수 선언
        FGGFInventoryItem& InventoryItem = GetInventoryItemReference(SlotIndex);

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
            UnregisterInventoryItemFromSlot(SlotIndex);

            // 인벤토리 슬롯에 들어있는 아이템 수량이 동일한 경우
            if(AmountToRemove <= 0) break;
        }
    }

    // 인벤토리 업데이트
    SetInventoryDirty();

    // 아이템 수량 통계 업데이트
    UpdateItemAmount(Item.ItemDefinition, -Item.Amount);

    return true;
}

bool UGGFInventoryManagerBase::SwapInventorySlots(const int32 SourceSlotIndex, const int32 TargetSlotIndex)
{
    // 서버에서만 호출 가능
    if(!GetOwner()->HasAuthority()) return false;

    // 지역 변수 초기화
    int32 SourceArrayIndex = InventoryIndexMap[SourceSlotIndex];
    int32 TargetArrayIndex = InventoryIndexMap[TargetSlotIndex];

    // 슬롯 인덱스 수정
    GetInventorySlotReference(SourceSlotIndex).Index = TargetSlotIndex;
    GetInventorySlotReference(TargetSlotIndex).Index = SourceSlotIndex;

    // 캐시 업데이트
    InventoryIndexMap[SourceSlotIndex] = TargetArrayIndex;
    InventoryIndexMap[TargetSlotIndex] = SourceArrayIndex;

    return true;
}

bool UGGFInventoryManagerBase::AddItemToEmptySlot(const FGGFInventoryItem& Item, int32& Remainder)
{
    // 변수 초기화
    Remainder = Item.Amount;

    // 인벤토리 빈 슬롯 인덱스 가져오기
    int32 EmptySlotIndex = GetEmptySlotIndex();
    if(EmptySlotIndex < 0) return false;

    // 빈 슬롯에 아이템 추가
    FGGFInventoryItem ItemToAdd = Item;
    ItemToAdd.Amount = FMath::Min(Item.Amount, Item.GetMaxStack());
    Remainder = Item.Amount - ItemToAdd.Amount;
    RegisterInventoryItemToSlot(ItemToAdd, EmptySlotIndex);

    // 아이템 추가 성공
    return true;
}

void UGGFInventoryManagerBase::UpdateItemAmount(UDataAsset* ItemDefinition, int32 InAmount)
{
    // 입력 유효성 검사
    if(ItemDefinition == nullptr || InAmount == 0) return;

    // 아이템 수량 업데이트
    int32 NewAmount = ItemAmountMap.Contains(ItemDefinition) ? ItemAmountMap[ItemDefinition] + InAmount : InAmount;
    NewAmount = FMath::Max(NewAmount, 0);
    ItemAmountMap.Emplace(ItemDefinition, NewAmount);
}

void UGGFInventoryManagerBase::RegisterInventoryItemToSlot(const FGGFInventoryItem& Item, int32 SlotIndex)
{
    // 인벤토리에 아이템 추가
    int32 ArrayIndex = Inventory.Slots.Emplace(SlotIndex, Item);

    // 인덱스 매핑
    InventoryIndexMap.Emplace(SlotIndex, ArrayIndex);
}

void UGGFInventoryManagerBase::UnregisterInventoryItemFromSlot(int32 SlotIndex)
{
    // 인벤토리에서 슬롯 제거
    int32 ArrayIndex = InventoryIndexMap[SlotIndex];
    Inventory.Slots.RemoveAtSwap(ArrayIndex);

    // RemoveSwap으로 인해 Index 순서가 보장되지 않기 때문에 캐시 초기화 진행
    CachingInventory();
}

void UGGFInventoryManagerBase::CachingInventory()
{
    // 인벤토리 맵 초기화
    InventoryIndexMap.Empty(Inventory.Slots.Num());
    ItemAmountMap.Empty(Inventory.Slots.Num());

    // 인벤토리 캐싱
    for (int32 ArrayIndex = 0; ArrayIndex < Inventory.Slots.Num(); ArrayIndex++)
    {
        // 지역 변수 초기화
        const FGGFInventorySlot& InventorySlot = Inventory.Slots[ArrayIndex];
        const int32 SlotIndex = InventorySlot.Index;
        const FGGFInventoryItem& InventoryItem = InventorySlot.Item;

        // 슬롯 인덱스 매핑
        InventoryIndexMap.Emplace(SlotIndex, ArrayIndex);

        // 아이템 수량 매핑
        UpdateItemAmount(InventoryItem.ItemDefinition, InventoryItem.Amount);
    }
}

int32 UGGFInventoryManagerBase::GetEmptySlotIndex() const
{
    for (int32 index = 0; index < MaxSlotNum; index++)
    {
        if(!InventoryIndexMap.Contains(index)) return index;
    }

    return -1;
}

TArray<int32> UGGFInventoryManagerBase::SearchItem(UDataAsset* ItemDefinition) const
{
    // 배열 선언
    TArray<int32> SortedSlotIndices;

    // 아이템 유효성 검사
    if(ItemDefinition == nullptr) return SortedSlotIndices;

    // 메모리 할당
    SortedSlotIndices.Reserve(InventoryIndexMap.Num());

    // 동일한 아이템 검색
    for(const auto& Slot : Inventory.Slots)
    {
        // 동일한 아이템이 들어있는 슬롯 인덱스 저장
        if(Slot == ItemDefinition) SortedSlotIndices.Emplace(Slot.Index);
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
