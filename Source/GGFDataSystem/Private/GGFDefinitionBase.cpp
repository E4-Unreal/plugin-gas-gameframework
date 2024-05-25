// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFDefinitionBase.h"

bool UGGFDefinitionBase::InitFromDataTable(UDataTable* NewDataTable, int32 NewID)
{
    // 입력 유효성 검사
    if(NewDataTable == nullptr || NewID < 0) return false;

    // 데이터 설정
    DataTable = NewDataTable;
    ID = NewID;

    // 초기화
    return Internal_InitFromDataTable();
}

bool UGGFDefinitionBase::Internal_InitFromDataTable_Implementation()
{
    // 데이터 테이블 구조체를 이용하여 데이터 에셋 초기화 진행
    return true;
}
