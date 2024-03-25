// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Animation/GEFirstPersonAnimInstance.h"

#include "GEGameplayTags.h"
#include "Logging.h"

UGEFirstPersonAnimInstance::UGEFirstPersonAnimInstance()
{
    TagsToRegister.AddTagFast(GEGameplayTags::State::Moving);
    TagsToRegister.AddTagFast(GEGameplayTags::State::ADS);
}

void UGEFirstPersonAnimInstance::OnGameplayEffectTagCountChanged_Event(const FGameplayTag Tag, int32 NewCount)
{
    Super::OnGameplayEffectTagCountChanged_Event(Tag, NewCount);

    const bool Value = NewCount > 0;

    using namespace GEGameplayTags::State;

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
