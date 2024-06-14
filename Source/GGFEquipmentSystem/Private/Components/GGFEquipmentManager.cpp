// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFEquipmentManager.h"

#include "GameplayTagContainer.h"
#include "Net/UnrealNetwork.h"
#include "GGFWeapon.h"
#include "Data/GGFEquipmentDataSubsystem.h"
#include "Data/GGFEquipmentDefinition.h"
#include "GGFEquipmentGameplayTags.h"

const FEquipmentSlot FEquipmentSlot::EmptySlot;

UGGFEquipmentManager::UGGFEquipmentManager()
{
    FEquipmentSlotConfig PrimarySlotConfig;
    PrimarySlotConfig.SlotTag = Equipment::Slot::Primary;
    PrimarySlotConfig.SocketNames.Emplace("weapon_waist");

    FEquipmentSlotConfig SecondarySlotConfig;
    SecondarySlotConfig.SlotTag = Equipment::Slot::Secondary;
    SecondarySlotConfig.SocketNames.Emplace("weapon_thigh_r");

    FEquipmentSlotConfig SpecialSlotConfig;
    SpecialSlotConfig.SlotTag = Equipment::Slot::Special;
    SpecialSlotConfig.SocketNames.Emplace(NAME_None);

    EquipmentSlotConfigs.Emplace(PrimarySlotConfig);
    EquipmentSlotConfigs.Emplace(SecondarySlotConfig);
    EquipmentSlotConfigs.Emplace(SpecialSlotConfig);
}

void UGGFEquipmentManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, SelectedEquipment);
}

void UGGFEquipmentManager::InitializeComponent()
{
    Super::InitializeComponent();

    // AvailableSlots로부터 EquipmentSlots를 생성합니다.
    CreateEquipmentSlots();
}

void UGGFEquipmentManager::BeginPlay()
{
    Super::BeginPlay();

    // 기본 장비를 추가합니다.
    AddDefaultEquipments();
}

void UGGFEquipmentManager::Activate(bool bReset)
{
    Super::Activate(bReset);

    // 모든 장비 숨김 해제
    HideEquipments(false);
}

void UGGFEquipmentManager::Deactivate()
{
    Super::Deactivate();

    // 모든 장비 숨기기
    HideEquipments(true);
}

void UGGFEquipmentManager::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    Super::OnComponentDestroyed(bDestroyingHierarchy);

    // TODO 옵션을 통해 파괴 대신 아이템 드랍으로 변경할 수 있는 기능 구현 필요
    // 모든 장비 파괴
    for (const auto& [EquipmentSlot, Equipment] : EquipmentSlots)
    {
        if(Equipment == nullptr) continue;
        Equipment->Destroy();
    }
}

bool UGGFEquipmentManager::AddEquipmentByID(int32 EquipmentID)
{
    if(auto GaminInstance = GetOwner()->GetGameInstance())
    {
        if(auto DataSubsystem = GaminInstance->GetSubsystem<UGGFEquipmentDataSubsystem>())
        {
            if(auto EquipmentDefinition = DataSubsystem->GetEquipmentDefinition(EquipmentID))
            {
                // 장비 데이터 가져오기
                const auto EquipmentData = EquipmentDefinition->GetData();

                // 장비를 추가할 수 있는지 확인
                if(!CanAddEquipment(EquipmentData.EquipmentClass)) return false;

                // 장비 스폰
                if(auto SpawnedEquipment = SpawnEquipment(EquipmentData.EquipmentClass))
                {
                    IGGFDataInterface::Execute_SetID(SpawnedEquipment, EquipmentID);

                    return AddEquipmentByActor(SpawnedEquipment);
                }
            }
        }
    }

    return false;
}

bool UGGFEquipmentManager::AddEquipmentByClass(TSubclassOf<AActor> EquipmentClass)
{
    // 장비를 추가할 수 있는지 확인
    if(!CanAddEquipment(EquipmentClass)) return false;

    // 장비 스폰 후 추가
    return AddEquipmentByActor(SpawnEquipment(EquipmentClass));
}

bool UGGFEquipmentManager::AddEquipmentByActor(AActor* EquipmentActor)
{
    // 입력 유효성 검사
    if(EquipmentActor == nullptr) return false;

    // 슬롯에 무기 추가
    const FGameplayTag& SlotTag = IGGFEquipmentInterface::Execute_GetEquipmentSlot(EquipmentActor);
    const FEquipmentSlot& EquipmentSlot = GetAvailableSlot(SlotTag);
    EquipmentSlots.Emplace(EquipmentSlot, EquipmentActor);

    if(!IsSelectedEquipmentExist())
    {
        // 선택 무기가 비어 있다면 새로운 무기를 선택 무기로 지정합니다.
        Server_SelectEquipment(EquipmentSlot.SlotTag, EquipmentSlot.Index);
    }
    else
    {
        // 선택 무기가 비어 있지 않은 경우 몸에 부착합니다.
        AttachEquipment(EquipmentActor, EquipmentSlot.SocketName);
    }

    return true;
}

void UGGFEquipmentManager::RemoveEquipment(FGameplayTag Slot, int32 Index)
{
    // 해당 슬롯에 장비 존재 유무 검사
    if(!IsEquipmentExist(Slot, Index)) return;

    // 장비 파괴
    const auto Equipment = GetEquipment(Slot, Index);
    Equipment->Destroy();

    // 슬롯 비우기
    ClearEquipmentSlot(Slot, Index);
}

void UGGFEquipmentManager::Server_SelectEquipment_Implementation(FGameplayTag Slot, int32 Index)
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
    IGGFEquipmentInterface::Execute_Activate(SelectedEquipment);
}

bool UGGFEquipmentManager::IsEquipmentExist(FGameplayTag Slot, int32 Index) const
{
    return GetEquipment(Slot, Index) != nullptr;
}

bool UGGFEquipmentManager::IsEquipmentSlotExist(FGameplayTag Slot, int32 Index) const
{
    return EquipmentSlots.Contains(FEquipmentSlot(Slot, Index));
}

AActor* UGGFEquipmentManager::GetEquipment(FGameplayTag Slot, int32 Index) const
{
    return IsEquipmentSlotExist(Slot, Index) ? *EquipmentSlots.Find(FEquipmentSlot(Slot, Index)) : nullptr;
}

void UGGFEquipmentManager::ClearEquipmentSlot(FGameplayTag Slot, int32 Index)
{
    // 장비 슬롯 유효성 검사
    if(!IsEquipmentSlotExist(Slot, Index)) return;

    // 장비 슬롯 비우기
    EquipmentSlots.Emplace(FEquipmentSlot(Slot, Index), nullptr);
}

void UGGFEquipmentManager::Deselect()
{
    if(SelectedEquipment)
    {
        // 기존 선택 무기를 비활성화합니다
        IGGFEquipmentInterface::Execute_Deactivate(SelectedEquipment);

        // TODO 애님 노티파이로 타이밍 결정할 수도
        // 손 대신 장비 슬롯에 부착합니다.
        AttachEquipment(SelectedEquipment, SelectedSlot.SocketName);
    }

    // 선택 슬롯을 비웁니다.
    SelectedSlot = FEquipmentSlot::EmptySlot;
    SelectedEquipment = nullptr;
}

bool UGGFEquipmentManager::AttachEquipment(AActor* Equipment, FName SocketName)
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

bool UGGFEquipmentManager::CanAddEquipment(TSubclassOf<AActor> EquipmentClass) const
{
    // 무기 슬롯이 비어있는지 확인
    const FGameplayTag& EquipmentSlot = GetEquipmentSlot(EquipmentClass);
    return GetOwner()->HasAuthority() && IsSlotAvailable(EquipmentSlot);
}

bool UGGFEquipmentManager::IsSlotAvailable(const FGameplayTag& InEquipmentSlot) const
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

const FEquipmentSlot& UGGFEquipmentManager::GetAvailableSlot(const FGameplayTag& WeaponSlot) const
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

void UGGFEquipmentManager::OnTargetMeshChanged()
{
    Super::OnTargetMeshChanged();

    // 기존 메시에 부착된 장비들을 새로운 메시에 부착
    for (const auto& [EquipmentSlot, Equipment] : EquipmentSlots)
    {
        AttachEquipment(Equipment, EquipmentSlot.SocketName);
    }

    // 선택 장비를 새로운 메시의 손 소켓에 부착
    AttachEquipment(SelectedEquipment, HandSocketName);
}

void UGGFEquipmentManager::HideEquipments(bool bHidden)
{
    // TODO 이미 숨겨진 장비들에 대한 플래그 설정 필요
    // 모든 장비 숨기기
    for (const auto& [EquipmentSlot, Equipment] : EquipmentSlots)
    {
        if(Equipment == nullptr) continue;
        Equipment->SetActorHiddenInGame(bHidden);
    }
}

void UGGFEquipmentManager::CreateEquipmentSlots()
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

void UGGFEquipmentManager::AddDefaultEquipments()
{
    for(auto EquipmentID : EquipmentIDList)
    {
        AddEquipmentByID(EquipmentID);
    }

    for (auto EquipmentClass : EquipmentClassList)
    {
        AddEquipmentByClass(EquipmentClass);
    }
}

void UGGFEquipmentManager::OnRep_SelectedEquipment(AActor* OldEquipment)
{
    // 중복 호출 검사
    if(SelectedEquipment == OldEquipment) return;

    // 기존 무기 비활성화
    if(OldEquipment && OldEquipment->Implements<UGGFEquipmentInterface>())
    {
        IGGFEquipmentInterface::Execute_Deactivate(OldEquipment);
    }

    // 새로운 무기 활성화
    if(SelectedEquipment && SelectedEquipment->Implements<UGGFEquipmentInterface>())
    {
        IGGFEquipmentInterface::Execute_Activate(SelectedEquipment);
    }
}
