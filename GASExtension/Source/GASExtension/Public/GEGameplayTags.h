#pragma once

#include "NativeGameplayTags.h"

namespace GEGameplayTags
{
    namespace State
    {
        /* 캐릭터 무브먼트 */
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(CrouchingTag) // 앉기
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(FallingTag) // 점프 혹은 낙하

        /* 캐릭터 상태 */
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(DeadTag) // 죽음
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(KnockdownTag) // 기절 (배그)
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(StunTag) // CC
    }
}
