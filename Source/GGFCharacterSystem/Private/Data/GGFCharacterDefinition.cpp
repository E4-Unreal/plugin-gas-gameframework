// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/GGFCharacterDefinition.h"

bool UGGFCharacterDefinition::InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase)
{
    // 구조체 캐스팅
    if(FGGFCharacterData* NewData = static_cast<FGGFCharacterData*>(NewDataTableRowBase))
    {
        // 데이터 설정
        Data = *NewData;
        return true;
    }

    return false;
}
