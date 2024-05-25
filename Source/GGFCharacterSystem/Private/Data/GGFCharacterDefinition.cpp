// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/GGFCharacterDefinition.h"

void UGGFCharacterDefinition::InitFromDataTable(UDataTable* DataTable, int32 ID)
{
    // 입력 유효성 검사
    if(DataTable == nullptr || ID < 0) return;

    // 데이터 설정
    if(FGGFCharacterDataTableRow* NewData = DataTable->FindRow<FGGFCharacterDataTableRow>(FName(FString::FromInt(ID)), ""))
    {
        Data.ID = ID;
        Data = *NewData;
    }
}
