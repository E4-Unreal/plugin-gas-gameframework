#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    /* 플레이어 입력 */
    namespace Input
    {
        namespace Skill
        {
            GGFSKILLSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
            GGFSKILLSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test)
            GGFSKILLSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Q)
            GGFSKILLSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(E)
        }
    }

    /* 스킬 */
    namespace Skill
    {
        namespace Cooldown
        {
            GGFSKILLSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
            GGFSKILLSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test)
            GGFSKILLSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Q)
            GGFSKILLSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(E)
        }
    }
}

using namespace GGFGameplayTags;
