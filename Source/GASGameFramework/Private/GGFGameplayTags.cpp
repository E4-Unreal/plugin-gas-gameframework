#include "GGFGameplayTags.h"

namespace GGFGameplayTags
{
    namespace State
    {
        /* 루트 태그 */
        UE_DEFINE_GAMEPLAY_TAG(State, "State")

        /* 캐릭터 무브먼트 */
        UE_DEFINE_GAMEPLAY_TAG(Moving, "State.Move") // 움직이는 상태 (걷기, 달리기, 전속력 달리기)
        UE_DEFINE_GAMEPLAY_TAG(Running, "State.Move.Run") // 달리기
        UE_DEFINE_GAMEPLAY_TAG(Sprinting, "State.Move.Run.Sprint") // 전속력 달리기
        UE_DEFINE_GAMEPLAY_TAG(Falling, "State.Falling") // 점프 혹은 낙하
        UE_DEFINE_GAMEPLAY_TAG(Crouching, "State.Crouching") // 앉기

        /* 캐릭터 상태 */
        UE_DEFINE_GAMEPLAY_TAG(Dead, "State.Dead") // 죽음
        UE_DEFINE_GAMEPLAY_TAG(Knockdown, "State.Knockdown") // 기절 (배그)
        UE_DEFINE_GAMEPLAY_TAG(Stun, "State.Stun") // CC
        UE_DEFINE_GAMEPLAY_TAG(ADS, "State.ADS") // 조준
    }

    namespace Input
    {
        /* 루트 태그 */
        UE_DEFINE_GAMEPLAY_TAG(Input, "Input")
    }

    namespace Action
    {
        /* 루트 태그 */
        UE_DEFINE_GAMEPLAY_TAG(Action, "Action")

        /* 행동 */
        UE_DEFINE_GAMEPLAY_TAG(Attack, "Action.Attack") // 공격
    }

    namespace Equipment
    {
        /* 루트 태그 */
        // 장비
        UE_DEFINE_GAMEPLAY_TAG(Equipment, "Equipment")

        // 무기
        namespace Weapon
        {
            UE_DEFINE_GAMEPLAY_TAG(Weapon, "Equipment.Weapon")

            // 화기
            namespace FireArm
            {
                UE_DEFINE_GAMEPLAY_TAG(Weapon, "Equipment.Weapon.FireArm")

                // 화기 부착물
                namespace Attachment
                {
                    UE_DEFINE_GAMEPLAY_TAG(Attachment, "Equipment.Weapon.FireArm.Attachment")

                    UE_DEFINE_GAMEPLAY_TAG(Muzzle, "Equipment.Weapon.FireArm.Attachment.Muzzle") // 총구
                    UE_DEFINE_GAMEPLAY_TAG(IronSight, "Equipment.Weapon.FireArm.Attachment.IronSight") // 가늠쇠
                    UE_DEFINE_GAMEPLAY_TAG(Scope, "Equipment.Weapon.FireArm.Attachment.Scope") // 조준경
                    UE_DEFINE_GAMEPLAY_TAG(Magazine, "Equipment.Weapon.FireArm.Attachment.Magazine") // 탄알집
                    UE_DEFINE_GAMEPLAY_TAG(Grip, "Equipment.Weapon.FireArm.Attachment.Grip") // 손잡이
                    UE_DEFINE_GAMEPLAY_TAG(Laser, "Equipment.Weapon.FireArm.Attachment.Laser") // 레이저
                }
            }
        }

        // 방어구
        namespace Armor
        {
            UE_DEFINE_GAMEPLAY_TAG(Armor, "Equipment.Armor")
        }

        // 장신구
        namespace Accessory
        {
            UE_DEFINE_GAMEPLAY_TAG(Armor, "Equipment.Accessory")
        }

        // 장비 슬롯
        namespace Slot
        {
            UE_DEFINE_GAMEPLAY_TAG(Slot, "Equipment.Slot")
        }
    }
}
