// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GFFAttachmentSlotInterface.h"
#include "Components/StaticMeshComponent.h"
#include "GFFAttachmentStaticMeshComponent.generated.h"

/**
 * GFFAttachmentManager 전용 스태틱 메시 컴포넌트 클래스로 GFFAttachmentSlotInterface를 구현하고 있습니다.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class GASGAMEFRAMEWORK_API UGFFAttachmentStaticMeshComponent : public UStaticMeshComponent, public IGFFAttachmentSlotInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config", meta = (Categories = "Equipment.Weapon.FireArm.Attachment"))
    FGameplayTag SlotTag;

public:
    UGFFAttachmentStaticMeshComponent();

    /* GFFAttachmentSlotInterface */
    FORCEINLINE virtual FGameplayTag GetSlotTag_Implementation() const override { return SlotTag; }
    virtual void SetMesh_Implementation(UStreamableRenderAsset* Mesh) override;
};
