// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFItemDefinition.h"
#include "GGFItemConfig_Pickup.generated.h"

/**
 * 스태틱 메시 피벗 기준
 */
UENUM(BlueprintType)
enum class EGGFStaticMeshPivot : uint8
{
    Center,
    Top,
    Bottom
};

/**
 * Pickup 초기화 전용 데이터 테이블 구조체입니다.
 * ItemDataSubsystem에서 PickupData로 변환 후 ItemConfig_Pickup 데이터 에셋을 생성하는데 사용됩니다.
 */
USTRUCT()
struct GGFITEMSYSTEM_API FGGFPickupTableRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UStaticMesh> StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGGFStaticMeshPivot Pivot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector RelativeLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator RelativeRotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector RelativeScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DefaultAmount;

    FGGFPickupTableRow()
    {
        StaticMesh = nullptr;
        Pivot = EGGFStaticMeshPivot::Center;
        RelativeLocation = FVector::ZeroVector;
        RelativeRotation = FRotator::ZeroRotator;
        RelativeScale = FVector::OneVector;
        DefaultAmount = 1;
    }
};

/**
 * Pickup 초기화 전용 구조체
 */
USTRUCT(BlueprintType)
struct GGFITEMSYSTEM_API FGGFPickupData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UStaticMesh> StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGGFStaticMeshPivot Pivot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FTransform Offset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 DefaultAmount;

    FGGFPickupData()
    {
        StaticMesh = nullptr;
        Pivot = EGGFStaticMeshPivot::Center;
        Offset = FTransform::Identity;
        DefaultAmount = 1;
    }

    bool IsValid() const { return StaticMesh != nullptr && DefaultAmount > 0; }
    bool IsNotValid() const { return !IsValid(); }

    FORCEINLINE FGGFPickupData& operator=(const FGGFPickupTableRow& PickupTableRow)
    {
        StaticMesh = PickupTableRow.StaticMesh;
        Pivot = PickupTableRow.Pivot;
        Offset = FTransform(PickupTableRow.RelativeRotation, PickupTableRow.RelativeLocation, PickupTableRow.RelativeScale);
        DefaultAmount = PickupTableRow.DefaultAmount;

        return *this;
    }
};

/**
 * Pickup 초기화 전용 데이터 에셋
 */
UCLASS()
class GGFITEMSYSTEM_API UGGFItemConfig_Pickup : public UGGFItemConfig
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetPickupData)
    FGGFPickupData PickupData;

public:
    virtual bool InitializeFromDataTable(FTableRowBase* TableRow) override;

public:
    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FGGFPickupData& GetPickupData() const { return PickupData; }

    virtual bool IsValid() const override { return PickupData.IsValid(); }
};
