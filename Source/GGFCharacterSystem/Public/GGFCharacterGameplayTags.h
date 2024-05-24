#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    /* 상태 */
    namespace State
    {
        GGFCHARACTERSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Moving) // 움직이는 상태 (걷기, 달리기, 전속력 달리기)
        GGFCHARACTERSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Running) // 달리기
        GGFCHARACTERSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sprinting) // 빠르게 달리기
        GGFCHARACTERSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Falling) // 점프 혹은 낙하
        GGFCHARACTERSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crouching) // 앉기
    }

    /* 플레이어 입력 */
    namespace Input
    {
        GGFCHARACTERSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sprint) // 빠르게 달리기
    }

}
