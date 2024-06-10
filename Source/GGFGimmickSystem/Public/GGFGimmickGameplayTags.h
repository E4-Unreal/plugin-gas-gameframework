#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    /* 게임플레이 큐 */
    namespace GameplayCue
    {
        namespace Teleport
        {
            GGFGIMMICKSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
            GGFGIMMICKSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)

            namespace In
            {
                GGFGIMMICKSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
                GGFGIMMICKSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)
            }

            namespace Out
            {
                GGFGIMMICKSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
                GGFGIMMICKSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)
            }
        }

        namespace Launch
        {
            GGFGIMMICKSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
            GGFGIMMICKSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)
        }

        namespace Button
        {
            GGFGIMMICKSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
            GGFGIMMICKSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)
            GGFGIMMICKSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Activate)
            GGFGIMMICKSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Deactivate)
        }
    }
}

using namespace GGFGameplayTags;
