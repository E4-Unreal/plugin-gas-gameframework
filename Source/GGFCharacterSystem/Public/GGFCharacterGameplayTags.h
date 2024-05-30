#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    /* 상태 */
    namespace State
    {
        GGFCHARACTERSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Moving) // 땅 위에서 움직이고 있는 상태
        GGFCHARACTERSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Running) // 달리고 있는 상태
        GGFCHARACTERSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sprinting) // 빠르게 달리고 있는 상태
        GGFCHARACTERSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Falling) // 체공 상태
        GGFCHARACTERSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crouching) // 앉아 있는 상태
        GGFCHARACTERSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Proning) // 누워 있는 상태
    }

    /* 플레이어 입력 */
    namespace Input
    {
        GGFCHARACTERSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sprint) // 빠르게 달리기 전용 입력 태그
    }

}
