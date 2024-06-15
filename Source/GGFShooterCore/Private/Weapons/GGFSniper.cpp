// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/GGFSniper.h"

#include "Blueprint/UserWidget.h"

void AGGFSniper::ShowScopeWidget(bool bShow)
{
    // 유효성 검사
    if(ScopeWidgetClass == nullptr) return;

    // 로컬 플레이어 UI 표시
    if(APawn* OwnerPawn = Cast<APawn>(GetOwner()))
    {
        if(OwnerPawn->IsPlayerControlled() && OwnerPawn->IsLocallyControlled())
        {
            if(bShow)
            {
                if(ScopeWidget == nullptr)
                {
                    ScopeWidget = CreateWidget(CastChecked<APlayerController>(OwnerPawn->Controller), ScopeWidgetClass);
                }

                ScopeWidget->AddToViewport();
            }
            else if(ScopeWidget)
            {
                ScopeWidget->RemoveFromParent();
            }
        }
    }
}
