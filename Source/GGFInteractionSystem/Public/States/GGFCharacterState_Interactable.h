// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GEGameplayStateMachine.h"
#include "GGFCharacterState_Interactable.generated.h"

/**
 * 상호작용 가능한 상태가 되면 지속적으로 캐릭터가 바라보는 방향으로 상호작용 오브젝트 감지 및 활성화를 시도합니다.
 */
UCLASS()
class GGFINTERACTIONSYSTEM_API UGGFCharacterState_Interactable : public UGECharacterState
{
    GENERATED_BODY()

protected:
#if WITH_EDITORONLY_DATA
    // 상호작용 가능한 오브젝트 탐지 디버그를 위한 옵션
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bShowDebug = false;
#endif

    // 스피어 트레이스에 사용되는 스피어 반경
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float SphereRadius = 20;

    // 스피어 트레이스 최대 거리
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float MaxDistance = 1000;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<AActor> InteractableActor;

public:
    UGGFCharacterState_Interactable();

protected:
    /* 메서드 */
    // 상호작용 가능한 오브젝트 탐색
    virtual void Scan(float DeltaTime);

    // 상호작용 가능한 오브젝트 활성화
    virtual void Activate();

    // 상호작용 가능한 오브젝트 비활성화
    virtual void Deactivate();

    /* GEGameplayState */

    virtual void OnTick_Implementation(float DeltaTime) override;
    virtual void OnExit_Implementation() override;
};
