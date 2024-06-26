// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Burst.h"
#include "GGFGameplayCueNotifyTypes.h"
#include "GGFGameplayCueNotify_Burst.generated.h"

/**
 * GameplayCueNotify_Burst에서 캐스케이드 파티클 시스템 옵션이 추가된 게임플레이 큐 노티파이 스태틱 클래스입니다.
 * 가능한 한 나이아가라 시스템을 사용하는 것이 바람직하지만 여건상 기존 에셋을 사용하기 위해 제작하였습니다.
 */
UCLASS(Meta = (DisplayName = "GGFGCN_Burst"))
class GGFCORE_API UGGFGameplayCueNotify_Burst : public UGameplayCueNotify_Burst
{
    GENERATED_BODY()

protected:
    // 스폰할 캐스케이드 파티클 시스템 목록
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GCN Defaults")
    TArray<FGGFGameplayCueNotify_CascadeInfo> CascadeParticles;

public:
    UGGFGameplayCueNotify_Burst();

protected:
    virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;
};
