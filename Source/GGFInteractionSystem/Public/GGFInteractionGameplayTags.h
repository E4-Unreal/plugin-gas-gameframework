#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    /* 상태 */
    namespace State
    {
        GGFINTERACTIONSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interactable) // 상호작용 가능한 상태
    }

    /* 입력 */
    namespace Input
    {
        GGFINTERACTIONSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interact) // 상호작용
    }
}
