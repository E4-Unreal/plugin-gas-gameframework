// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFInteractableActor.h"
#include "GGFInteractableActorWithUI.generated.h"

class UGGFInteractionMenu;

/**
 * 상호작용 시 UI 화면을 띄워주는 기능이 추가된 InteractableActor 클래스입니다.
 *
 * 기기 조작 등에 적합합니다.
 */
UCLASS()
class GGFINTERACTIONSYSTEM_API AGGFInteractableActorWithUI : public AGGFInteractableActor
{
    GENERATED_BODY()

protected:
    // 상호작용을 수행한 플레이어 화면에 띄워줄 위젯 클래스입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UUserWidget> WidgetClass;

    // 로컬 플레이어에게만 보여줄 위젯이기 때문에 인스턴스는 오직 한 개만 존재하므로 굳이 파괴할 필요가 없습니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UUserWidget> Widget;

public:
    /* GGFInteractableInterface */
    virtual bool StartInteraction_Implementation(AActor* OtherActor) override;
    virtual bool Deactivate_Implementation(AActor* OtherActor) override;

protected:
    // 상호작용 시작 시 위젯을 생성합니다.
    virtual void CreateLocalPlayerWidget(APlayerController* PlayerController);
};
