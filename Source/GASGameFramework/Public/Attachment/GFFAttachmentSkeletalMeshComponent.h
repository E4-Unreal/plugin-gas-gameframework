// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GFFAttachmentSlotInterface.h"
#include "Components/SkeletalMeshComponent.h"
#include "GFFAttachmentSkeletalMeshComponent.generated.h"

/**
 * GFFAttachmentManager 전용 스켈레탈 메시 컴포넌트 클래스로 GFFAttachmentSlotInterface를 구현하고 있습니다.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class GASGAMEFRAMEWORK_API UGFFAttachmentSkeletalMeshComponent : public USkeletalMeshComponent, public IGFFAttachmentSlotInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    FGameplayTag SlotTag;

public:
    UGFFAttachmentSkeletalMeshComponent();

    /* GFFAttachmentSlotInterface */
    FORCEINLINE virtual FGameplayTag GetSlotTag_Implementation() const override { return SlotTag; }
    virtual void SetMesh_Implementation(UStreamableRenderAsset* Mesh) override;
};
