#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    /* 상태 */
    namespace State
    {
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Moving) // 움직이는 상태 (걷기, 달리기, 전속력 달리기)
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Running) // 달리기
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sprinting) // 전속력 달리기
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Falling) // 점프 혹은 낙하
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crouching) // 앉기
    }
}
