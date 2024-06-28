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

            namespace Type
            {
                GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
                GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)
                GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test)
            }
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

        namespace Locomotion
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Moving)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Running)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sprinting)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Falling)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crouching)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Proning)
        }

        namespace Buff
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용

            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Invinsible)

            namespace Immunity
            {
                GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
                GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용
            }
        }

        namespace Debuff
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test) // 테스트 전용

            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Snare)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stun)
        }
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
