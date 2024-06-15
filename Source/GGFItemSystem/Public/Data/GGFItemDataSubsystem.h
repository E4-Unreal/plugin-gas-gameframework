// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GGFItemDataSubsystem.generated.h"

struct FGGFItemData;
class UGGFItemDefinition;

/**
 * 런타임에 데이터 테이블로부터 데이터 에셋 생성 및 관리를 담당하는 서브 시스템 클래스입니다.
 */
UCLASS()
class GGFITEMSYSTEM_API UGGFItemDataSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

protected:
    // 데이터 에셋 목록
    UPROPERTY(Transient)
    TArray<TObjectPtr<UGGFItemDefinition>> ItemList;

    // 데이터 에셋의 ID 매핑 정보
    UPROPERTY(Transient)
    TMap<int32, TObjectPtr<UGGFItemDefinition>> ItemMap;

public:
    /* Subsystem */

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /* API */

    // 데이터 테이블로부터 직접 데이터를 읽어오는 메서드로 런타임이 아닌 상황에서 사용합니다.
    UFUNCTION(BlueprintPure, Category = "Item")
    static const FGGFItemData& GetData(int32 ID);

    // 모든 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Item")
    const FORCEINLINE TArray<UGGFItemDefinition*>& GetAllDefinitions() const { return ItemList; }

    // ID에 대응하는 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Item")
    FORCEINLINE UGGFItemDefinition* GetDefinition(int32 ID) const { return ItemMap.Contains(ID) ? ItemMap[ID] : nullptr; }

protected:
    // 데이터 서브 시스템 동기화
    virtual void FetchDataSubsystem();
};
