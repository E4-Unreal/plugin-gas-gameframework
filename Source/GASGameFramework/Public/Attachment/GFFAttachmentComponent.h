// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GFFAttachmentComponent.generated.h"

/**
 * 부착물 전용 스태틱 메시 컴포넌트입니다.
 * GFFAttachmentManager의 StaticMeshComponentClass에서 사용할 목적으로 작성되었습니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGFFAttachmentComponent : public UStaticMeshComponent
{
    GENERATED_BODY()

public:
    UGFFAttachmentComponent();
};
