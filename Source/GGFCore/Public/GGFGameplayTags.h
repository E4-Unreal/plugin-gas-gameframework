#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    /* 데이터 */
    namespace Data
    {
        namespace Damage
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(True)
        }

        namespace Attribute
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Health)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mana)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shield)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stamina)
        }

        namespace MaxAttribute
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Health)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mana)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shield)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stamina)
        }

        namespace AttributeRegenRate
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Health)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mana)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shield)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stamina)
        }

        namespace Stat
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attack)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Defense)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(MoveSpeed)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttackSpeed)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AbilityHaste)
        }

        namespace MaxStat
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attack)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Defense)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(MoveSpeed)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttackSpeed)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AbilityHaste)
        }
    }

    /* 상태 */
    namespace State
    {
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Knockdown)
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dead)
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Respawn)
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Reviving)

        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Snare)
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stun)

        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Invinsible)
    }

    /* 게임플레이 큐 */
    namespace GameplayCue
    {
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
    }

    /* 행동 */
    namespace Action
    {
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용

        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attack) // 공격
    }

    /* 플레이어 입력 */
    namespace Input
    {
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
    }

    /* 이벤트 */
    namespace Event
    {
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
    }

    /* 데미지 */
    namespace Damage
    {
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트

        namespace Type
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default) // 기본
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
        }
    }

    /* 버프 */
    namespace Buff
    {
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용

        /* 면역 */
        namespace Immunity
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
        }
    }

    /* 디버프 */
    namespace Debuff
    {
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
    }

    /* 오브젝트 */
    namespace Object
    {
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트

        namespace Type
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
        }
    }

    namespace Skill
    {
        namespace Cooldown
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test)
        }
    }
}

using namespace GGFGameplayTags;
