// Fill out your copyright notice in the Description page of Project Settings.

#include "Tests/GGFTestDefinition.h"

bool UGGFTestDefinition::InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase)
{
    // 구조체 캐스팅
    if(FTestDataTableRow* NewTestData = static_cast<FTestDataTableRow*>(NewDataTableRowBase))
    {
        // 데이터 설정
        TestData = *NewTestData;
        return true;
    }

    return false;
}
