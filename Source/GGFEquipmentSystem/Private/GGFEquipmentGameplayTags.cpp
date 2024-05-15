#include "GGFEquipmentGameplayTags.h"

namespace GGFGameplayTags
{
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
            UE_DEFINE_GAMEPLAY_TAG(Slot, "Equipment.Slot") // 루트
            UE_DEFINE_GAMEPLAY_TAG(Primary, "Equipment.Slot.Primary") // 주 장비 슬롯
            UE_DEFINE_GAMEPLAY_TAG(Secondary, "Equipment.Slot.Secondary") // 보조 장비 슬롯
            UE_DEFINE_GAMEPLAY_TAG(Special, "Equipment.Slot.Special") // 특수 장비 슬롯
        }
    }
}
