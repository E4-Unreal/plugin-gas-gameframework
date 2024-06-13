// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTags.h"
#include "GGFCharacterAnimationInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, Blueprintable)
class GGFEQUIPMENTSYSTEM_API UGGFCharacterAnimationInterface : public UInterface
{
    GENERATED_BODY()
};

// TODO 몽타주 섹션 처리
// TODO 다른 모듈로 이전
/**
 * 캐릭터 애니메이션 제어를 위한 인터페이스
 */
class GGFEQUIPMENTSYSTEM_API IGGFCharacterAnimationInterface
{
    GENERATED_BODY()

public:
    // 애님 인스턴스 클래스 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetAnimInstanceClass(TSubclassOf<UAnimInstance> NewAnimInstanceClass);

    // 애님 몽타주 재생 (멀티캐스트)
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void PlayAnimMontage(UAnimMontage* NewAnimMontage, float PlayRate = 1);
};
