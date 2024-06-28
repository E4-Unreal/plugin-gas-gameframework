#include "GGFGameplayTags.h"

namespace GGFGameplayTags
{
    /* 데이터 */
    namespace Data
    {
        namespace Damage
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Data.Damage", "일반 데미지")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(True, "Data.Damage.True", "고정 데미지")

            namespace Type
            {
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Data.Damage.Type", "데미지 타입")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "Data.Damage.Type.Default", "기본 데미지 타입")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Data.Damage.Type.Test", "테스트 전용 데미지 타입")
            }
        }

        namespace Attribute
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Health, "Data.Attribute.Health", "체력")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Mana, "Data.Attribute.Mana", "마나")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Shield, "Data.Attribute.Shield", "실드")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stamina, "Data.Attribute.Stamina", "스태미나")
        }

        namespace MaxAttribute
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Health, "Data.MaxAttribute.Health", "최대 체력")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Mana, "Data.MaxAttribute.Mana", "최대 마나")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Shield, "Data.MaxAttribute.Shield", "최대 실드")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stamina, "Data.MaxAttribute.Stamina", "최대 스태미나")
        }

        namespace AttributeRegenRate
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Health, "Data.AttributeRegenRate.Health", "체력 재생")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Mana, "Data.AttributeRegenRate.Mana", "마나 재생")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Shield, "Data.AttributeRegenRate.Shield", "실드 재생")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stamina, "Data.AttributeRegenRate.Stamina", "스태미나 재생")
        }

        namespace Stat
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, "Data.Stat.Attack", "공격력")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Defense, "Data.Stat.Defense", "방어력")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(MoveSpeed, "Data.Stat.MoveSpeed", "이동 속도")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttackSpeed, "Data.Stat.AttackSpeed", "공격 속도")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(AbilityHaste, "Data.Stat.AbilityHaste", "스킬 가속")
        }

        namespace MaxStat
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, "Data.MaxStat.Attack", "최대 공격력")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Defense, "Data.MaxStat.Defense", "최대 방어력")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(MoveSpeed, "Data.MaxStat.MoveSpeed", "최대 이동 속도")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttackSpeed, "Data.MaxStat.AttackSpeed", "최대 공격 속도")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(AbilityHaste, "Data.MaxStat.AbilityHaste", "최대 스킬 가속")
        }
    }

    /* 상태 */
    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "State", "상태")

        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Knockdown, "State.Knockdown", "죽기 직전의 상태로 부활 전까지 행동 불가")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Dead, "State.Dead", "죽음")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Respawn, "State.Respawn", "부활 중인 상태입니다.")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Reviving, "State.Reviving", "다른 플레이어를 부활시키는 중인 상태입니다.")

        namespace Locomotion
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Moving, "State.Locomotion.Moving", "땅 위에서 움직이고 있는 상태")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Running, "State.Locomotion.Moving.Running", "달리고 있는 상태")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Sprinting, "State.Locomotion.Moving.Sprinting", "빠르게 달리고 있는 상태")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Falling, "State.Locomotion.Falling", "체공 상태")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Crouching, "State.Locomotion.Crouching", "앉아 있는 상태")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Proning, "State.Locomotion.Proning", "누워 있는 상태")
        }

        namespace Buff
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "State.Buff", "버프")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "State.Buff.Test", "테스트 전용 버프")

            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Invinsible, "State.Buff.Invinsible", "데미지가 들어가지 않는 무적 상태")

            namespace Immunity
            {
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "State.Buff.Immunity", "특정 데미지 타입에 대한 면역")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "State.Buff.Immunity.Test", "테스트 전용 면역")
            }
        }

        namespace Debuff
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "State.Debuff", "디버프")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "State.Debuff.Test", "테스트 전용 디버프")

            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Snare, "State.Debuff.Snare", "속박 상태로 이동이 불가능해집니다.")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stun, "State.Debuff.Stun", "행동이 불가능한 상태")
        }
    }

    /* 게임플레이 큐 */
    namespace GameplayCue
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue", "게임플레이 큐")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "GameplayCue.Test", "테스트 전용 게임플레이 큐")
    }

    /* 행동 */
    namespace Action
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Action", "행동")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Action.Test", "테스트 전용 행동")

        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, "Action.Attack", "공격")
    }

    /* 플레이어 입력 */
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Input", "플레이어 입력")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Input.Test", "테스트 전용 플레이어 입력")
    }

    /* 이벤트 */
    namespace Event
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Event", "게임플레이 이벤트")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Event.Test", "테스트 전용 게임플레이 이벤트")
    }

    /* 오브젝트 */
    namespace Object
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Object", "오브젝트")

        namespace Type
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Object.Type", "오브젝트 타입")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Object.Type.Test", "테스트 전용 오브젝트 타입")
        }
    }

    namespace Skill
    {
        namespace Cooldown
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Skill.Cooldown", "스킬 전용 입력 태그")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Skill.Cooldown.Test", "테스트 전용 스킬 입력 태그")
        }
    }
}
