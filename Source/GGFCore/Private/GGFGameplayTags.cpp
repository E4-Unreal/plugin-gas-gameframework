#include "GGFGameplayTags.h"

namespace GGFGameplayTags
{
    namespace Data
    {
        namespace Damage
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Data.Damage", "일반 데미지")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(True, "Data.Damage.True", "고정 데미지")
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

    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "State", "상태")

        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Knockdown, "State.Knockdown", "죽기 직전의 상태로 부활 전까지 행동 불가")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Dead, "State.Dead", "죽음")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Respawn, "State.Respawn", "부활 중인 상태입니다.")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Reviving, "State.Reviving", "다른 플레이어를 부활시키는 중인 상태입니다.")

        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Snare, "State.Snare", "속박 상태로 이동이 불가능해집니다.")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stun, "State.Stun", "행동이 불가능한 상태")

        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Invinsible, "State.Invinsible", "데미지가 들어가지 않는 무적 상태")
    }
}
