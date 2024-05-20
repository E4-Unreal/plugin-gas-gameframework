// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFInteractableInterface.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class GGFINTERACTIONSYSTEM_API UGGFInteractableInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 상호작용을 위한 인터페이스로 상호작용이 가능한 오브젝트에 구현하면 됩니다.
 */
class GGFINTERACTIONSYSTEM_API IGGFInteractableInterface
{
    GENERATED_BODY()

public:
    // 상호 작용과 관련된 이벤트를 활성화합니다.
    // Ex) 플레이어가 바라보는 경우 UI 표시
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool Activate(AActor* OtherActor);

    // 상호 작용과 관련된 이벤트를 비활성화합니다.
    // Ex) 플레이어가 다른 곳을 바라보는 경우 UI 숨기기
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool Deactivate(AActor* OtherActor);

    // 상호작용 시작
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool StartInteraction(AActor* OtherActor);

    // 상호작용 중단
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool StopInteraction(AActor* OtherActor);
};
