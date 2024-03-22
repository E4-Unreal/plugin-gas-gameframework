// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEAnimInstance.h"
#include "GEFirstPersonAnimInstance.generated.h"

/**
 * FPS 애니메이션을 위한 애님 인스턴스 클래스입니다.
 * LowPolyShooterPack 애니메이션 에셋 구성에 맞추어 작성되었습니다.
 */
UCLASS()
class GASEXTENSION_API UGEFirstPersonAnimInstance : public UGEAnimInstance
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool bMoving;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool bRunning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool bSprinting;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool bADS;

public:
    UGEFirstPersonAnimInstance();

protected:
    virtual void OnGameplayEffectTagCountChanged_Event(const FGameplayTag Tag, int32 NewCount) override;
};
