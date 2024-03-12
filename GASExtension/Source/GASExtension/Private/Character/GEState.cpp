// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GEState.h"

#include "Character/GEStateMachine.h"

void UGEState::Init(UGEStateMachine* InStateMachine)
{
    // null 검사
    if(InStateMachine == nullptr) return;

    // 중복 호출 방지
    if(bInitialized) return;
    bInitialized = true;

    // 상태 머신 레퍼런스 할당
    StateMachine = InStateMachine;

    // 초기화 진행
    OnInit();
}

void UGEState::Enter(const FGameplayTag& Tag)
{
    // 트리거에 속한 태그인지 확인
    if(!Tag.MatchesAny(Triggers)) return;

    // 해당 태그가 이미 활성화된 상태면 무시
    if(Tag.MatchesAnyExact(ActivatedTriggers)) return;

    // 활성화된 태그 목록에 추가
    ActivatedTriggers.AddTagFast(Tag);

    // Enter 로직 실행
    OnEnter();
}

void UGEState::Exit(const FGameplayTag& Tag)
{
    // 트리거에 속한 태그인지 확인
    if(!Tag.MatchesAny(Triggers)) return;

    // 해당 태그가 활성화된 상태가 아니라면 무시
    if(!Tag.MatchesAnyExact(ActivatedTriggers)) return;

    // 활성화된 태그 목록에서 제거
    ActivatedTriggers.RemoveTag(Tag);

    // 아직 활성화된 상태라면 무시
    if(IsActivated()) return;

    // Exit 로직 실행
    OnExit();
}

void UGEState::OnInit_Implementation()
{
}

void UGEState::OnEnter_Implementation()
{
}

void UGEState::OnExit_Implementation()
{
}
