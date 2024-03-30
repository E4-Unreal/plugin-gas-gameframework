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
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetAttachmentMesh)
    TObjectPtr<UStaticMesh> AttachmentMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetSlot)
    FGameplayTag Slot;

public:
    UFUNCTION(BlueprintGetter)
    FORCEINLINE UStaticMesh* GetAttachmentMesh() const { return AttachmentMesh; }

    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FGameplayTag& GetSlot() const { return Slot; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsValid() const { return AttachmentMesh && Slot.IsValid(); }
};
