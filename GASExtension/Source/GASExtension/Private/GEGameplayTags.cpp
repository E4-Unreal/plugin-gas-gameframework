#include "GEGameplayTags.h"

namespace GEGameplayTags
{
    namespace State
    {
        /* 루트 태그 */
        UE_DEFINE_GAMEPLAY_TAG(StateTag, "State")

        /* 캐릭터 무브먼트 */
        UE_DEFINE_GAMEPLAY_TAG(CrouchingTag, "State.Crouching") // 앉기
        UE_DEFINE_GAMEPLAY_TAG(FallingTag, "State.Falling") // 점프 혹은 낙하

        /* 캐릭터 상태 */
        UE_DEFINE_GAMEPLAY_TAG(DeadTag, "State.Dead") // 죽음
        UE_DEFINE_GAMEPLAY_TAG(KnockdownTag, "State.Knockdown") // 기절 (배그)
        UE_DEFINE_GAMEPLAY_TAG(StunTag, "State.Stun") // CC
        UE_DEFINE_GAMEPLAY_TAG(ADSTag, "State.ADS") // 조준
    }

    namespace Input
    {
        /* 루트 태그 */
        UE_DEFINE_GAMEPLAY_TAG(InputTag, "Input")
    }

    namespace Action
    {
        /* 루트 태그 */
        UE_DEFINE_GAMEPLAY_TAG(ActionTag, "Action")

        /* 행동 */
        UE_DEFINE_GAMEPLAY_TAG(AttackTag, "Action.Attack") // 공격
    }

    namespace Equipment
    {
        /* 루트 태그 */
        // 장비
        UE_DEFINE_GAMEPLAY_TAG(EquipmentTag, "Equipment")
        UE_DEFINE_GAMEPLAY_TAG(WeaponTag, "Equipment.Weapon")
        UE_DEFINE_GAMEPLAY_TAG(ArmorTag, "Equipment.Armor")

        // 슬롯
        UE_DEFINE_GAMEPLAY_TAG(SlotTag, "Equipment.Slot")
    }
}
