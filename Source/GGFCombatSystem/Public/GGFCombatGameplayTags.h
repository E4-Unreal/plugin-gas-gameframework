#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    /* 게임플레이 큐 */
    namespace GameplayCue
    {
        namespace Hit
        {
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default) // 기본
        }

        namespace Explosion
        {
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default) // 기본
        }

        namespace Bounce
        {
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default) // 기본
        }
    }

    /* 데미지 */
    namespace Damage
    {
        namespace Type
        {
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Physical) // 물리
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fire) // 불
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Water) // 물
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Electricity) // 전기
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ice) // 얼음

            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Gravity) // 중력
        }
    }

    /* 버프 */
    namespace Buff
    {
        /* 면역 */
        namespace Immunity
        {
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Physical) // 물리
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fire) // 불
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Water) // 물
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Electricity) // 전기
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ice) // 얼음
        }
    }

    /* 오브젝트 */
    namespace Object
    {
        namespace Type
        {
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Physical) // 물리
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fire) // 불
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Water) // 물
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Electricity) // 전기
            GGFCOMBATSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ice) // 얼음
        }
    }
}
