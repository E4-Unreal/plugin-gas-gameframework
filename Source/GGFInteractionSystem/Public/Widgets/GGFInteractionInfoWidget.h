// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/GGFInteractionInfoWidgetInterface.h"
#include "GGFInteractionInfoWidget.generated.h"

class UTextBlock;

/**
 * 상호작용 오브젝트 정보 표시를 위한 위젯 클래스
 */
UCLASS()
class GGFINTERACTIONSYSTEM_API UGGFInteractionInfoWidget : public UUserWidget, public IGGFInteractionInfoWidgetInterface
{
    GENERATED_BODY()

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> DisplayNameText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> InteractionInfoText;

public:
    /* GGFInteractionInfoWidgetInterface */

    virtual void SetDisplayName_Implementation(const FText& NewDisplayName) override;
    virtual void SetInteractionInfo_Implementation(const FText& NewInteractionInfo) override;

};
