// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/GGFCharacterDefinition.h"

const FGGFCharacterData FGGFCharacterData::EmptyCharacterData;

bool UGGFCharacterDefinition::InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase)
{
    // 구조체 캐스팅
    if(auto NewData = static_cast<FGGFCharacterData*>(NewDataTableRowBase))
    {
        // 데이터 설정
        Data = *NewData;
        return true;
    }

    return false;
}
