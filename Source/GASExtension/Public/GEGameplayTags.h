#pragma once

#include "GGFGameplayTags.h"

namespace GGFGameplayTags
{
    /* 게임플레이 큐 */
    namespace GameplayCue
    {
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
    }

    /* 행동 */
    namespace Action
    {
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용

        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attack) // 공격
    }

    /* 플레이어 입력 */
    namespace Input
    {
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
    }

    /* 이벤트 */
    namespace Event
    {
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
    }

    /* 데미지 */
    namespace Damage
    {
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트

        namespace Type
        {
            GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default) // 기본
            GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
        }
    }

    /* 버프 */
    namespace Buff
    {
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용

        /* 면역 */
        namespace Immunity
        {
            GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
        }
    }

    /* 디버프 */
    namespace Debuff
    {
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
    }

    /* 오브젝트 */
    namespace Object
    {
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트

        namespace Type
        {
            GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
        }
    }

    namespace Skill
    {
        namespace Cooldown
        {
            GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
            GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test)
        }
    }
}
