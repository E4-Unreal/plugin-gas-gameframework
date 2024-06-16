// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFDataManager.h"

#include "Net/UnrealNetwork.h"

UGGFDataManager::UGGFDataManager()
{
    SetIsReplicatedByDefault(true);
}

void UGGFDataManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, ID);
}

void UGGFDataManager::InitializeComponent()
{
    Super::InitializeComponent();

    SetID(ID);
}

void UGGFDataManager::SetID(int32 NewID)
{
    ID = NewID;

    FetchData();

    OnIDUpdated.Broadcast(NewID);
}

void UGGFDataManager::FetchData()
{
    // TODO ID에 대응하는 데이터 가져오기
}

void UGGFDataManager::OnRep_ID(int32 OldID)
{
    SetID(ID);
}
