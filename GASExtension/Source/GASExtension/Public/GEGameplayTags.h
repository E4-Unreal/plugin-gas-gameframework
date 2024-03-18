#pragma once

#include "NativeGameplayTags.h"

namespace GEGameplayTags
{
    namespace State
    {
        /* 캐릭터 무브먼트 */
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(CrouchingTag) // 앉기
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(FallingTag) // 점프 혹은 낙하
    }
}
