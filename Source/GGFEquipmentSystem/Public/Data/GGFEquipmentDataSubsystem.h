// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GGFEquipmentDataSubsystem.generated.h"

struct FGGFWeaponData;
class UGGFWeaponDefinition;
struct FGGFEquipmentData;
class UGGFEquipmentDefinition;

/**
 * 런타임에 데이터 테이블로부터 데이터 에셋 생성 및 관리를 담당하는 서브 시스템 클래스입니다.
 */
UCLASS()
class GGFEQUIPMENTSYSTEM_API UGGFEquipmentDataSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

protected:
    // 데이터 에셋 목록
    UPROPERTY(Transient)
    TArray<TObjectPtr<UGGFEquipmentDefinition>> EquipmentList;

    // 데이터 에셋의 ID 매핑 정보
    UPROPERTY(Transient)
    TMap<int32, TObjectPtr<UGGFEquipmentDefinition>> EquipmentMap;

    // 데이터 에셋 목록
    UPROPERTY(Transient)
    TArray<TObjectPtr<UGGFWeaponDefinition>> WeaponList;

    // 데이터 에셋의 ID 매핑 정보
    UPROPERTY(Transient)
    TMap<int32, TObjectPtr<UGGFWeaponDefinition>> WeaponMap;

public:
    /* Subsystem */

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /* API */

    // 데이터 테이블로부터 직접 데이터를 읽어오는 메서드로 런타임이 아닌 상황에서 사용합니다.
    UFUNCTION(BlueprintPure, Category = "Equipment")
    static bool GetEquipmentData(int32 ID, FGGFEquipmentData& Data);

    // 모든 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Equipment")
    const FORCEINLINE TArray<UGGFEquipmentDefinition*>& GetAllEquipmentDefinitions() const { return EquipmentList; }

    // ID에 대응하는 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Equipment")
    FORCEINLINE UGGFEquipmentDefinition* GetEquipmentDefinition(int32 ID) const { return EquipmentMap.Contains(ID) ? EquipmentMap[ID] : nullptr; }

    // 데이터 테이블로부터 직접 데이터를 읽어오는 메서드로 런타임이 아닌 상황에서 사용합니다.
    UFUNCTION(BlueprintPure, Category = "Weapon")
    static bool GetWeaponData(int32 ID, FGGFWeaponData& Data);

    // 모든 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Weapon")
    const FORCEINLINE TArray<UGGFWeaponDefinition*>& GetAllWeaponDefinitions() const { return WeaponList; }

    // ID에 대응하는 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, Category = "Weapon")
    FORCEINLINE UGGFWeaponDefinition* GetWeaponDefinition(int32 ID) const { return WeaponMap.Contains(ID) ? WeaponMap[ID] : nullptr; }

protected:
    // 데이터 서브 시스템 동기화
    virtual void FetchDataSubsystem();
};
