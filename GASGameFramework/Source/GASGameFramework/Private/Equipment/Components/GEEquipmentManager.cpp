// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Components/GEEquipmentManager.h"

#include "GameplayTagContainer.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/GEWeapon.h"

const FEquipmentSlot FEquipmentSlot::EmptySlot;

void UGEEquipmentManager::InitializeComponent()
{
    Super::InitializeComponent();

    // AvailableSlots로부터 EquipmentSlots를 생성합니다.
    CreateEquipmentSlots();

    // 기본 장비를 추가합니다.
    AddDefaultEquipments();
}

void UGEEquipmentManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, SelectedEquipment);
}

bool UGEEquipmentManager::AddEquipment(TSubclassOf<AGEEquipment> EquipmentClass)
{
    // 무기를 추가할 수 있는지 확인
    if(!CanAddEquipment(EquipmentClass)) return false;

    // 무기 스폰
    AGEEquipment* SpawnedEquipment = SpawnEquipment(EquipmentClass);
    if(SpawnedEquipment == nullptr) return false;

    // 슬롯에 무기 추가
    const FGameplayTag& SlotTag = SpawnedEquipment->GetEquipmentSlot();
    const FEquipmentSlot& EquipmentSlot = GetAvailableSlot(SlotTag);
    EquipmentSlots.Emplace(EquipmentSlot, SpawnedEquipment);

    if(!IsSelectedEquipmentExist())
    {
        // 선택 무기가 비어 있다면 새로운 무기를 선택 무기로 지정합니다.
        SelectEquipment(EquipmentSlot.SlotTag, EquipmentSlot.Index);
    }
    else
    {
        // 선택 무기가 비어 있지 않은 경우 몸에 부착합니다.
        AttachEquipment(SpawnedEquipment, EquipmentSlot.SocketName);
    }

    return true;
}

void UGEEquipmentManager::RemoveEquipment(FGameplayTag Slot, int32 Index)
{
    // 해당 슬롯에 장비 존재 유무 검사
    if(!IsEquipmentExist(Slot, Index)) return;

    // 장비 파괴
    const auto Equipment = GetEquipment(Slot, Index);
    Equipment->Destroy();

    // 슬롯 비우기
    ClearEquipmentSlot(Slot, Index);
}

void UGEEquipmentManager::SelectEquipment(FGameplayTag Slot, int32 Index)
{
    // 이미 선택된 슬롯이면 무시
    const FEquipmentSlot& EquipmentSlot = FEquipmentSlot(Slot, Index);
    if(SelectedSlot == EquipmentSlot) return;

    // 새로 선택할 장비가 존재하는지 확인합니다.
    if(!IsEquipmentExist(Slot, Index)) return;

    // 현재 선택 장비를 집어넣습니다.
    Deselect();

    // 새로운 선택 장비를 설정하고 손에 부착합니다.
    SelectedSlot = EquipmentSlot;
    SelectedEquipment = GetEquipment(SelectedSlot.SlotTag, SelectedSlot.Index);
    AttachEquipment(SelectedEquipment, HandSocketName);

    // 선택 장비를 활성화합니다.
    if(AGEWeapon* Weapon = Cast<AGEWeapon>(SelectedEquipment))
    {
        Weapon->OnSelected_Implementation();
    }
}

bool UGEEquipmentManager::IsEquipmentExist(FGameplayTag Slot, int32 Index) const
{
    return GetEquipment(Slot, Index) != nullptr;
}

bool UGEEquipmentManager::IsEquipmentSlotExist(FGameplayTag Slot, int32 Index) const
{
    return EquipmentSlots.Contains(FEquipmentSlot(Slot, Index));
}

AGEEquipment* UGEEquipmentManager::GetEquipment(FGameplayTag Slot, int32 Index) const
{
    return IsEquipmentSlotExist(Slot, Index) ? *EquipmentSlots.Find(FEquipmentSlot(Slot, Index)) : nullptr;
}

void UGEEquipmentManager::ClearEquipmentSlot(FGameplayTag Slot, int32 Index)
{
    // 장비 슬롯 유효성 검사
    if(!IsEquipmentSlotExist(Slot, Index)) return;

    // 장비 슬롯 비우기
    EquipmentSlots.Emplace(FEquipmentSlot(Slot, Index), nullptr);
}

void UGEEquipmentManager::Deselect()
{
    // TODO 자연스러운 연출을 위해 나중에 애님 노티파이에서 호출하도록 해야합니다. bool 값으로 즉시 자동으로 호출될지 정할 것 같습니다.

    // 기존 선택 무기를 비활성화합니다
    // 선택 장비를 활성화합니다.
    if(AGEWeapon* Weapon = Cast<AGEWeapon>(SelectedEquipment))
    {
        Weapon->OnDeselected_Implementation();
    }

    // 손 대신 장비 슬롯에 부착합니다.
    AttachEquipment(SelectedEquipment, SelectedSlot.SocketName);

    // 선택 슬롯을 비웁니다.
    SelectedSlot = FEquipmentSlot::EmptySlot;
    SelectedEquipment = nullptr;
}

bool UGEEquipmentManager::AttachEquipment(AGEEquipment* Equipment, FName SocketName)
{
    if(Super::AttachEquipment(Equipment, SocketName))
    {
        // 숨겨진 장비의 경우 다시 보여줍니다.
        if(Equipment->IsHidden()) Equipment->SetActorHiddenInGame(false);
        return true;
    }
    else
    {
        // 부착에 실패한 경우 장비를 숨깁니다.
        if(Equipment)
            Equipment->SetActorHiddenInGame(true);

        return false;
    }
}

bool UGEEquipmentManager::CanAddEquipment(TSubclassOf<AGEEquipment> EquipmentClass) const
{
    // 무기 슬롯이 비어있는지 확인
    const FGameplayTag& EquipmentSlot = GetEquipmentSlot(EquipmentClass);
    return EquipmentClass != nullptr && IsSlotAvailable(EquipmentSlot) && GetOwner()->HasAuthority();
}

bool UGEEquipmentManager::IsSlotAvailable(const FGameplayTag& InEquipmentSlot) const
{
    for (const auto& [EquipmentSlot, Equipment] : EquipmentSlots)
    {
        // 장착 가능한 슬롯이 아닌 경우 무시
        if(EquipmentSlot != InEquipmentSlot) continue;

        // 이미 추가된 장비가 있는 경우 무시
        if(Equipment != nullptr) continue;

        // 빈 슬롯 발견
        return true;
    }

    return false;
}

const FEquipmentSlot& UGEEquipmentManager::GetAvailableSlot(const FGameplayTag& WeaponSlot) const
{
    for (const auto& [EquipmentSlot, Equipment] : EquipmentSlots)
    {
        // 장착 가능한 슬롯이 아닌 경우 무시
        if(EquipmentSlot != WeaponSlot) continue;

        // 이미 추가된 장비가 있는 경우 무시
        if(Equipment != nullptr) continue;

        // 빈 슬롯 발견
        return EquipmentSlot;
    }

    return FEquipmentSlot::EmptySlot;
}

void UGEEquipmentManager::CreateEquipmentSlots()
{
    for (const FEquipmentSlotConfig& EquipmentSlotConfig : EquipmentSlotConfigs)
    {
        const TArray<FName>& SocketNames = EquipmentSlotConfig.SocketNames;

        for(int i = 0; i < SocketNames.Num(); i++)
        {
            FEquipmentSlot EquipmentSlot
            {
                EquipmentSlotConfig.SlotTag,
                i,
                SocketNames[i]
            };

            // 손 소켓과 장비 소켓은 중복될 수 없습니다.
            if(EquipmentSlot.SocketName == HandSocketName)
                EquipmentSlot.SocketName = NAME_None;

            EquipmentSlots.Add(EquipmentSlot);
        }
    }
}

void UGEEquipmentManager::AddDefaultEquipments()
{
    for (const auto& DefaultEquipment : DefaultEquipments)
    {
        AddEquipment(DefaultEquipment);
    }
}

void UGEEquipmentManager::OnRep_SelectedEquipment(AGEEquipment* OldEquipment)
{
    // TODO Deactivate OldEquipment

    // TODO Activate NewEquipment
}
