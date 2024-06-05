#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    /* 게임플레이 큐 */
    namespace GameplayCue
    {
        namespace Hit
        {
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default) // 기본
        }

        namespace Explosion
        {
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default) // 기본
        }

        namespace Bounce
        {
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default) // 기본
        }
    }

    /* 데미지 */
    namespace Damage
    {
        namespace Type
        {
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Physical) // 물리
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fire) // 불
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Water) // 물
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Electricity) // 전기
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ice) // 얼음

            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Gravity) // 중력
        }
    }

    /* 버프 */
    namespace Buff
    {
        /* 면역 */
        namespace Immunity
        {
            GGFCOMBATCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Physical) // 물리
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
