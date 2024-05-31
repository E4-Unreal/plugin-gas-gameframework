#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    /* 데미지 */
    namespace Damage
    {
        namespace Type
        {
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Physical) // 물리
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Gravity) // 중력
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fire) // 불
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Water) // 물
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Electricity) // 전기
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ice) // 얼음
        }
    }

    /* 오브젝트 */
    namespace Object
    {
        namespace Type
        {
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Physical) // 물리
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fire) // 불
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Water) // 물
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Electricity) // 전기
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ice) // 얼음
        }
    }
}
