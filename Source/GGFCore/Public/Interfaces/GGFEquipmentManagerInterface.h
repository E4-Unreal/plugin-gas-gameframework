// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFEquipmentManagerInterface.generated.h"

UINTERFACE()
class GGFCORE_API UGGFEquipmentManagerInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 장비 관리 전용 컴포넌트를 위한 인터페이스
 */
class GGFCORE_API IGGFEquipmentManagerInterface
{
    GENERATED_BODY()

public:
    // 현재 손에 장착 중인 장비 가져오기
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    AActor* GetSelectedEquipment() const;

    // 스폰된 장비를 추가합니다.
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool AddEquipmentByActor(AActor* EquipmentActor);

    // 장비 클래스에 대응하는 장비를 스폰 후 추가합니다.
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool AddEquipmentByClass(TSubclassOf<AActor> EquipmentClass);

    // ID에 대응하는 장비를 스폰 후 추가합니다.
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool AddEquipmentByID(int32 EquipmentID);
};
