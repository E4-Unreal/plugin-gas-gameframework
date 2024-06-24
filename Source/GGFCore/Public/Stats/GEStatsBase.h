// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/GEAttributeSetBase.h"
#include "GEStatsBase.generated.h"

/**
 * 일반적인 게임에서 사용되는 스탯 시스템의 기본 요소인 스탯을 정의하기 위한 AttributeSet 클래스입니다.
 * 기능적으로는 AttributeSet과 동일하지만 일반적인 Attribute, 즉 체력, 마나 등과 달리 자연 재생 수치가 존재하지 않습니다.
 *
 * 현재는 블루프린트 설정에서 서브 클래스를 통해 구분해주기 위해 클래스를 나누었을뿐 기능적으로 다른 점은 없습니다.
 */
UCLASS()
class GGFCORE_API UGEStatsBase : public UGEAttributeSetBase
{
    GENERATED_BODY()
};
