// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDefinitionBase.h"
#include "GGFWeaponDefinition.generated.h"

// TODO 1인칭 추가
/**
 * 무기 데이터 테이블 구조체
 */
USTRUCT()
struct GGFEQUIPMENTSYSTEM_API FGGFWeaponData : public FGGFDataTableRowBase
{
    GENERATED_BODY()

    static const FGGFWeaponData EmptyWeaponData;

    // 무기 장착 시간
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spec")
    float EquipDuration = 1.5f;

    // 무기 장착 해제 시간
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spec")
    float UnequipDuration = 1.5f;

    // 무기 애니메이션 클래스
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Character")
    TSubclassOf<UAnimInstance> WeaponAnimClass;

    // 캐릭터 애니메이션 클래스
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Character")
    TSubclassOf<UAnimInstance> CharacterAnimClass;

    // 무기 장착 애니메이션
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Character")
    TObjectPtr<UAnimMontage> EquipMontage;

    // 무기 장착 해제 애니메이션
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Character")
    TObjectPtr<UAnimMontage> UnequipMontage;

    // 기본 생성자
    FGGFWeaponData() { }
};

/**
 * 무기 데이터 에셋
 */
UCLASS(BlueprintType, Blueprintable)
class GGFEQUIPMENTSYSTEM_API UGGFWeaponDefinition : public UGGFDefinitionBase
{
    GENERATED_BODY()

protected:
    // 아이템 정의를 위한 데이터
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetData, Category = "Config")
    FGGFWeaponData Data;

public:
    /* GGFDefinitionBase */

    virtual bool InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase) override;

    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FGGFWeaponData& GetData() const { return Data; }
};
