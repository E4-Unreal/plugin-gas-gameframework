// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "GGFDefinitionBase.h"
#include "GGFEquipmentDefinition.generated.h"

class UGameplayEffect;
class UGameplayAbility;

/**
 * 장비 정의를 위한 데이터 테이블 구조체
 */
USTRUCT()
struct GGFEQUIPMENTSYSTEM_API FGGFEquipmentData : public FGGFDataTableRowBase
{
    GENERATED_BODY()

    // 장비 슬롯 아이콘
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UTexture2D> Icon;

    // 기본 스켈레탈 메시
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USkeletalMesh> SkeletalMesh;

    // 장비 종류
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Equipment"))
    FGameplayTag EquipmentType;

    // 장비 슬롯
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Equipment.Slot"))
    FGameplayTag EquipmentSlot;

    // 공격력
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    float Attack;

    // 방어력
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    float Defense;

    // 이동 속도
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    float MoveSpeed;

    // 공격 속도
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    float AttackSpeed;

    // 스킬 쿨감
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    float AbilityHaste;
};

/**
 * 장비 정의를 위한 데이터 에셋
 */
UCLASS(BlueprintType, Blueprintable)
class GGFEQUIPMENTSYSTEM_API UGGFEquipmentDefinition : public UGGFDefinitionBase
{
    GENERATED_BODY()

protected:
    // 아이템 정의를 위한 데이터
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetData, Category = "Config")
    FGGFEquipmentData Data;

    // 장비 스탯 전용 게임플레이 이펙트
    UPROPERTY(EditAnywhere, BlueprintGetter = GetStats, Category = "Config")
    TObjectPtr<UGameplayEffect> Stats;

protected:
    // 스탯 전용 게임플레이 이펙트 생성
    virtual UGameplayEffect* CreateStatsEffect();

    // 스탯 전용 게임플레이 이펙트에 추가할 Modifier
    virtual FGameplayModifierInfo CreateModifier(const FGameplayAttribute& Attribute, float Value, EGameplayModOp::Type ModOp = EGameplayModOp::Additive);

public:
    /* GGFDefinitionBase */

    virtual bool InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase) override;

    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FGGFEquipmentData& GetData() const { return Data; }

    UFUNCTION(BlueprintGetter)
    UGameplayEffect* GetStats() const { return Stats; }
};
