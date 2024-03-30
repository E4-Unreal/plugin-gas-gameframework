// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "GFFAttachmentSlotInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGFFAttachmentSlotInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 부착물 부착을 위한 인터페이스로 StaticMeshComponent와 SkeletalMeshComponent에서 구현됩니다.
 */
class GASGAMEFRAMEWORK_API IGFFAttachmentSlotInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FGameplayTag GetSlotTag() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetMesh(UStreamableRenderAsset* Mesh);
};
