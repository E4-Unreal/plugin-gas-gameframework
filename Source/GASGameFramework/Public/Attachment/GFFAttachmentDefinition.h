// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GFFAttachmentDefinition.generated.h"

// TODO 추후 캐릭터 장비, 탈것 커스터마이징 등에서도 사용할 수 있습니다.
/**
 * 총기 부품 장착에 사용하기 위한 데이터 에셋 클래스입니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGFFAttachmentDefinition : public UDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetStaticMesh)
    TObjectPtr<UStaticMesh> StaticMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetSkeletalMesh)
    TObjectPtr<USkeletalMesh> SkeletalMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetSlot, meta = (Categories = "Equipment.Weapon.FireArm.Attachment"))
    FGameplayTag Slot;

public:
    UFUNCTION(BlueprintGetter)
    FORCEINLINE UStaticMesh* GetStaticMesh() const { return StaticMesh; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USkeletalMesh* GetSkeletalMesh() const { return SkeletalMesh; }

    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FGameplayTag& GetSlot() const { return Slot; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsValid() const { return Slot.IsValid() && (StaticMesh || SkeletalMesh); }
};
