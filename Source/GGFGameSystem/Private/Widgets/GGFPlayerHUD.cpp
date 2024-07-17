// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFPlayerHUD.h"

#include "GGFGameState.h"
#include "Widgets/GGFPlayerWidget.h"

void UGGFPlayerHUD::NativeConstruct()
{
    Super::NativeConstruct();

    // 위젯 변수 할당
    TeamPlayerWidgets.Emplace(TeamPlayerWidget_1);
    TeamPlayerWidgets.Emplace(TeamPlayerWidget_2);
    TeamPlayerWidgets.Emplace(TeamPlayerWidget_3);

    // 초기화
    LocalPlayerWidget->SetPlayerState(GetOwningPlayerState());
    LocalPlayerWidget->SetVisibility(ESlateVisibility::HitTestInvisible);

    // 이벤트 바인딩
    if(auto CastedGameState = GetWorld()->GetGameState<AGGFGameState>())
    {
        FetchTeamSlots();
        CastedGameState->OnTeamInfoUpdated.AddDynamic(this, &ThisClass::OnTeamInfoUpdated);
    }
    else
    {
        GetWorld()->GameStateSetEvent.AddUObject(this, &ThisClass::OnGameStateSet);
    }
}

void UGGFPlayerHUD::OnTeamInfoUpdated(APlayerState* Player, const FGGFTeamInfo& OldTeamInfo,
    const FGGFTeamInfo& NewTeamInfo)
{
    FetchTeamSlots();
}

void UGGFPlayerHUD::OnGameStateSet(AGameStateBase* GameState)
{
    if(auto CastedGameState = GetWorld()->GetGameState<AGGFGameState>())
    {
        FetchTeamSlots();
        CastedGameState->OnTeamInfoUpdated.AddDynamic(this, &ThisClass::OnTeamInfoUpdated);
    }
}

void UGGFPlayerHUD::FetchTeamSlots_Implementation()
{
    if(auto GameState = GetWorld()->GetGameState<AGGFGameState>())
    {
        TeamSlots = GameState->GetTeamSlotsByPlayer(GetOwningPlayerState());
        int32 TeamPlayerCount = 0;
        for (const auto& TeamSlot : TeamSlots)
        {
            if(TeamSlot.PlayerState != GetOwningPlayerState())
            {
                TeamPlayerWidgets[TeamPlayerCount]->SetPlayerState(TeamSlot.PlayerState);
                TeamPlayerWidgets[TeamPlayerCount]->SetVisibility(ESlateVisibility::HitTestInvisible);
                ++TeamPlayerCount;
            }
        }

        // 할당되지 않은 위젯 비활성화
        for(int32 Index = TeamPlayerCount; Index < TeamPlayerWidgets.Num(); ++Index)
        {
            TeamPlayerWidgets[Index]->SetVisibility(ESlateVisibility::Hidden);
        }
    }
    else
    {
        for (auto TeamPlayerWidget : TeamPlayerWidgets)
        {
            TeamPlayerWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}
