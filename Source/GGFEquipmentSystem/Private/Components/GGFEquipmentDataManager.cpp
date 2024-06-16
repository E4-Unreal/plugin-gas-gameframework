// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFEquipmentDataManager.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Data/GGFEquipmentDataSubsystem.h"
#include "Data/GGFEquipmentDefinition.h"
#include "Logging.h"

void UGGFEquipmentDataManager::InitializeComponent()
{
    Super::InitializeComponent();

    bValid = bValid && EquipmentDefinition != nullptr;
}

const FGGFEquipmentData& UGGFEquipmentDataManager::GetEquipmentData() const
{
    return EquipmentDefinition ? EquipmentDefinition->GetData() : UGGFEquipmentDataSubsystem::GetEquipmentData(ID);
}

void UGGFEquipmentDataManager::ApplyStatsEffectToTarget(AActor* Target)
{
    if(auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target))
    {
        if(GetEquipmentDefinition())
        {
            ActiveStatsEffectHandle = TargetSystem->ApplyGameplayEffectToSelf(
                    GetEquipmentDefinition()->GetStats(),
                    UGameplayEffect::INVALID_LEVEL,
                    TargetSystem->MakeEffectContext()
                    );
        }
    }
}

void UGGFEquipmentDataManager::RemoveStatsEffectFromTarget(AActor* Target)
{
    if(auto TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target))
    {
        TargetSystem->RemoveActiveGameplayEffect(ActiveStatsEffectHandle);
        ActiveStatsEffectHandle.Invalidate();
    }
}

void UGGFEquipmentDataManager::FetchData()
{
    Super::FetchData();

    // 중복 호출 방지
    if(EquipmentDefinition && EquipmentDefinition->GetID() == ID) return;

    // 초기화
    EquipmentDefinition = nullptr;

    // 데이터 가져오기
    if(auto EquipmentDataSubsystem = GetDataSubsystem<UGGFEquipmentDataSubsystem>())
    {
        EquipmentDefinition = EquipmentDataSubsystem->GetEquipmentDefinition(ID);
    }
}
