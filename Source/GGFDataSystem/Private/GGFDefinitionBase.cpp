// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFDefinitionBase.h"

bool UGGFDefinitionBase::InitFromDataTable(UDataTable* NewDataTable, int32 NewID)
{
    // 데이터 에셋 유효성 초기화
    bValid = false;

    // 입력 유효성 검사
    if(NewDataTable == nullptr || NewID < 0) return false;

    // 디버깅 편의성을 위해 초기화 성공 여부와 관계없이 데이터 설정 진행
    DataTable = NewDataTable;
    ID = NewID;

    // 데이터 유효성 검사
    FGGFDataTableRowBase* NewDataPtr = NewDataTable->FindRow<FGGFDataTableRowBase>(FName(FString::FromInt(NewID)), "");
    if(NewDataPtr == nullptr || NewDataPtr->IsNotValid()) return false;

    // 초기화 진행
    bValid = InitFromDataTableRowBase(NewDataPtr);

    return bValid;
}

bool UGGFDefinitionBase::InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase)
{
    // 데이터 테이블 구조체를 이용하여 데이터 에셋 초기화 진행

    return true;
}
