// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup/GGFPickupInstance.h"

void AGGFPickupInstance::BeginPlay()
{
    Super::BeginPlay();

    // 기본 설정된 데이터로 초기화 진행
    if(DefaultItemDefinition)
        InitFromItemDefinition(DefaultItemDefinition);
    else
        InitFromItemConfig(DefaultItemConfig);
}

#if WITH_EDITOR
void AGGFPickupInstance::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    const FName DefaultItemDefinitionName = GET_MEMBER_NAME_CHECKED(ThisClass, DefaultItemDefinition);
    const FName DefaultItemConfigName = GET_MEMBER_NAME_CHECKED(ThisClass, DefaultItemConfig);

    FProperty* MemberPropertyThatChanged = PropertyChangedEvent.MemberProperty;
    const FName MemberPropertyName = MemberPropertyThatChanged != NULL ? MemberPropertyThatChanged->GetFName() : NAME_None;

    const bool bDefaultItemConfigChanged = MemberPropertyName == DefaultItemDefinitionName || MemberPropertyName == DefaultItemConfigName;

    if(bDefaultItemConfigChanged)
    {
        if(DefaultItemDefinition)
            InitFromItemDefinition(DefaultItemDefinition);
        else
            InitFromItemConfig(DefaultItemConfig);

        bIsInitialized = false;
    }

    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
