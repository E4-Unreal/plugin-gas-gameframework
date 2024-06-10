// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GGFTriggerBox.h"
#include "GGFInteractableActor.generated.h"

class UGGFInteractableComponent;

/**
 * InteractableArea 범위 안에 들어온 모든 플레이어 폰에 Interactable 상태 태그를 부여합니다.
 * 추가로 로컬 플레이어 폰인 경우에는 외곽선과 UI를 표시합니다.
 *
 * 수집할 수 있는 아이템이나 버튼처럼 단순한 상호작용 오브젝트에 적합합니다.
 */
UCLASS()
class GGFINTERACTIONSYSTEM_API AGGFInteractableActor : public AGGFTriggerBox
{
    GENERATED_BODY()

public:
    /* 서브 오브젝트 이름 */

    static FName InteractableComponentName;

private:
    /* 컴포넌트 */

    // 상호작용 안내를 위한 UI
    UPROPERTY(VisibleAnywhere, BlueprintGetter = "GetInteractableComponent", Category = "Component")
    TObjectPtr<UGGFInteractableComponent> InteractableComponent;

public:
    AGGFInteractableActor();

    /* Actor */

    virtual void PostInitializeComponents() override;

protected:
    /* 이벤트 */

    UFUNCTION(BlueprintNativeEvent)
    void OnPawnInteract(APawn* OtherPawn);

    UFUNCTION(BlueprintNativeEvent)
    void OnLocalPawnInteract(APawn* OtherLocalPawn);

    UFUNCTION(BlueprintNativeEvent)
    void OnPawnBeginOverlap(APawn* OtherPawn);

    UFUNCTION(BlueprintNativeEvent)
    void OnPawnEndOverlap(APawn* OtherPawn);

    UFUNCTION(BlueprintNativeEvent)
    void OnLocalPawnBeginOverlap(APawn* OtherLocalPawn);

    UFUNCTION(BlueprintNativeEvent)
    void OnLocalPawnEndOverlap(APawn* OtherLocalPawn);

protected:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFInteractableComponent* GetInteractableComponent() const { return InteractableComponent; }
};
