// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Animation/GGFFirstPersonAnimInstance.h"

#include "GGFGameplayTags.h"
#include "Logging.h"

UGGFFirstPersonAnimInstance::UGGFFirstPersonAnimInstance()
{
    // 몽타주 슬롯 연동
    bUseMainInstanceMontageEvaluationData = true;

    // 바인딩 태그 등록
    TagsToRegister.AddTagFast(GGFGameplayTags::State::Moving);
    TagsToRegister.AddTagFast(GGFGameplayTags::State::ADS);
}

void UGGFFirstPersonAnimInstance::OnGameplayEffectTagCountChanged_Event(const FGameplayTag Tag, int32 NewCount)
{
    Super::OnGameplayEffectTagCountChanged_Event(Tag, NewCount);

    const bool Value = NewCount > 0;

    using namespace GGFGameplayTags::State;

    if(Tag.MatchesTag(Moving))
        bMoving = Value;

    if(Tag.MatchesTag(Running))
        bRunning = Value;

    if(Tag.MatchesTag(Sprinting))
        bSprinting = Value;

    if(Tag.MatchesTag(ADS))
        bADS = Value;

    if(!Tag.MatchesAny(TagsToRegister))
    {
#if WITH_EDITOR
        LOG_CALLINFO_COMMENT(LogGASExtension, Warning, TEXT("태그 이벤트가 등록되었지만 사용되지 않고 있습니다: %s"), *Tag.GetTagName().ToString())
#endif
    }
}
