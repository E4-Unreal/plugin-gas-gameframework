// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/GGFCharacterSkinDefinition.h"

bool UGGFCharacterSkinDefinition::InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase)
{
    // 구조체 캐스팅
    if(FGGFCharacterSkinData* NewData = static_cast<FGGFCharacterSkinData*>(NewDataTableRowBase))
    {
        // 데이터 설정
        Data = *NewData;
        return true;
    }

    return false;
}
