// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFInteractableActor.h"
#include "GGFInteractableMenuActor.generated.h"

class UGGFInteractionMenu;

/**
 * 상호작용 시 관련 메뉴 위젯을 보여주는 기능이 추가된 InteractableActor 클래스입니다.
 *
 * 창고, 상점 등에 적합합니다.
 */
UCLASS()
class GGFINTERACTIONSYSTEM_API AGGFInteractableMenuActor : public AGGFInteractableActor
{
    GENERATED_BODY()

protected:
    // 상호작용을 수행한 플레이어 화면에 띄워줄 위젯 클래스입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UUserWidget> MenuWidgetClass;

    // 로컬 플레이어에게만 보여줄 위젯이기 때문에 인스턴스는 오직 한 개만 존재하므로 굳이 파괴할 필요가 없습니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UUserWidget> MenuWidget;

public:
    AGGFInteractableMenuActor();

    /* InteractableActorBase */

    virtual void OnLocalPawnInteract_Implementation(APawn* OtherLocalPawn) override;
    virtual void OnLocalPawnEndOverlap_Implementation(APawn* OtherLocalPawn) override;

protected:
    // 상호작용 시작 시 위젯을 생성합니다.
    virtual void CreateLocalPlayerWidget(APawn* LocalPlayer);
};
