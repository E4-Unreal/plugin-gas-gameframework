#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    namespace State
    {
        /* 캐릭터 무브먼트 */
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Moving) // 움직이는 상태 (걷기, 달리기, 전속력 달리기)
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Running) // 달리기
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sprinting) // 전속력 달리기
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Falling) // 점프 혹은 낙하
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crouching) // 앉기

        /* 캐릭터 상태 */
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(ADS) // 조준
    }

    /* 입력 */
    namespace Input
    {
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input) // 루트
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fire) // 총기 발사
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(ADS) // 총기 조준
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Reload) // 총기 재장전
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interact) // 상호작용
    }
}
