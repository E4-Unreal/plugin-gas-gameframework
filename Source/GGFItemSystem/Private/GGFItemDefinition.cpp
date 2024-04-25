// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFItemDefinition.h"

bool UGGFItemDefinition::InitializeFromDataTable(int32 InID, FTableRowBase* InData, const TArray<TObjectPtr<UGGFItemConfig>>& InConfigs)
{
    if(FGGFItemTableRow* ItemData = static_cast<FGGFItemTableRow*>(InData))
    {
        ID = InID;
        DisplayName = ItemData->DisplayName;
        Configs = InConfigs;

        return true;
    }

    return false;
}

UGGFItemConfig* UGGFItemDefinition::FindConfigByClass(TSubclassOf<UGGFItemConfig> ConfigClass)
{
    if(ConfigClass)
    {
        for (auto Config : Configs)
        {
            if(Config && Config->GetClass()->IsChildOf(ConfigClass)) return Config;
        }

        for(auto InstancedConfig : InstancedConfigs)
        {
            if(InstancedConfig && InstancedConfig->GetClass()->IsChildOf(ConfigClass)) return InstancedConfig;
        }
    }

    return nullptr;
}
