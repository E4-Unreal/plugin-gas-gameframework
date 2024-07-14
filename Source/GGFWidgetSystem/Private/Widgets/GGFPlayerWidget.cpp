// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFPlayerWidget.h"

#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"
#include "Widgets/GGFActorWidget.h"

void UGGFPlayerWidget::SetPlayerState(APlayerState* NewPlayerState)
{
    ensure(NewPlayerState);

    // PlayerState 교체
    auto OldPlayerState = PlayerState;
    PlayerState = NewPlayerState;

    // 기존 PlayerState로부터 이벤트 언바인딩
    if(OldPlayerState.IsValid())
    {
        UnbindPlayerStateEvents(OldPlayerState.Get());
    }

    // 새로운 PlayerState에 이벤트 바인딩
    if(PlayerState.IsValid())
    {
        BindPlayerStateEvents(PlayerState.Get());
    }

    // PlayerName 설정
    if(PlayerState.IsValid())
    {
        PlayerNameText->SetText(FText::FromString(PlayerState->GetPlayerName()));
    }

    // PlayerPawnWidget 업데이트
    UpdatePlayerPawnWidget();
}

void UGGFPlayerWidget::UpdatePlayerPawnWidget()
{
    if(GetPlayerPawnWidget())
    {
        // 대상 Pawn 변경
        GetPlayerPawnWidget()->SetActor(PlayerState->GetPawn());
    }
}

void UGGFPlayerWidget::BindPlayerStateEvents(APlayerState* NewPlayerState)
{
    NewPlayerState->OnPawnSet.AddDynamic(this, &ThisClass::OnPlayerStatePawnSet);
}

void UGGFPlayerWidget::UnbindPlayerStateEvents(APlayerState* OldPlayerState)
{
    OldPlayerState->OnPawnSet.RemoveDynamic(this, &ThisClass::OnPlayerStatePawnSet);
}

void UGGFPlayerWidget::OnPlayerStatePawnSet(APlayerState* Player, APawn* NewPawn, APawn* OldPawn)
{
    UpdatePlayerPawnWidget();
}
