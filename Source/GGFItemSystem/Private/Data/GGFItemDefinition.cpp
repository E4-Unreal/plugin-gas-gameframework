﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/GGFItemDefinition.h"

const FGGFItemData FGGFItemData::EmptyItemData;

bool UGGFItemDefinition::InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase)
{
    // 구조체 캐스팅
    if(auto NewData = static_cast<FGGFItemData*>(NewDataTableRowBase))
    {
        // 데이터 설정
        Data = *NewData;
        return true;
    }

    return false;
}
