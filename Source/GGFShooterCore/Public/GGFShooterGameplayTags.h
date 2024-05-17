#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    /* 상태 */
    namespace State
    {
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(ADS) // 조준
    }

    /* 입력 */
    namespace Input
    {
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fire) // 총기 발사
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(ADS) // 총기 조준
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Reload) // 총기 재장전
    }
}
