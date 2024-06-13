// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFEquipmentDataManager.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Data/GGFEquipmentDataSubsystem.h"
#include "Data/GGFEquipmentDefinition.h"
#include "Logging.h"

void UGGFEquipmentDataManager::PostInitProperties()
{
    Super::PostInitProperties();

    bValid = EquipmentDefinition != nullptr;
}

FGGFEquipmentData UGGFEquipmentDataManager::GetData() const
{
    if(EquipmentDefinition)
    {
        return EquipmentDefinition->GetData();
    }
    else
    {
        FGGFEquipmentData UncachedData;
        bool bFound = UGGFEquipmentDataSubsystem::GetData(ID, UncachedData);

#if WITH_EDITOR
        if(!bFound)
        {
            LOG_ACTOR_COMPONENT_DETAIL(Error, TEXT("해당 ID(%d)에 대응하는 데이터를 찾을 수 없습니다."), ID)
        }
#endif

        return UncachedData;
    }
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

void UGGFEquipmentDataManager::SetID(int32 NewID)
{
    EquipmentDefinition = nullptr;
    if(auto EquipmentDataSubsystem = GetDataSubsystem<UGGFEquipmentDataSubsystem>())
    {
        EquipmentDefinition = EquipmentDataSubsystem->GetDefinition(ID);
    }

    Super::SetID(NewID);
}
