// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/GGFMenuWidget.h"
#include "GGFInteractionMenuWidget.generated.h"

// TODO 에디터 상에서 UI 조작 중 캐릭터가 죽으면 다른 클라이언트 플레이어의 입력이 먹통이 되는 버그가 발견되었습니다. 빌드 테스트는 아직입니다.
/**
 * 상호작용 오브젝트의 상호작용 시 로컬 플레이어에게 표시할 위젯 클래스입니다.
 */
UCLASS()
class GGFINTERACTIONSYSTEM_API UGGFInteractionMenuWidget : public UGGFMenuWidget
{
    GENERATED_BODY()
};
