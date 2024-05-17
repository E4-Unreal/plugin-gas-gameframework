#include "GGFEquipmentGameplayTags.h"

namespace GGFGameplayTags
{
    /* 장비 */
    namespace Equipment
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "Equipment") // 루트

        /* 무기 */
        namespace Weapon
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Equipment.Weapon") // 루트
        }

        /* 방어구 */
        namespace Armor
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Equipment.Armor") // 루트
        }

        /* 장신구 */
        namespace Accessory
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Equipment.Accessory") // 루트
        }

        /* 장비 슬롯 */
        namespace Slot
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Equipment.Slot") // 루트
            UE_DEFINE_GAMEPLAY_TAG(Primary, "Equipment.Slot.Primary") // 주 슬롯
            UE_DEFINE_GAMEPLAY_TAG(Secondary, "Equipment.Slot.Secondary") // 보조 슬롯
            UE_DEFINE_GAMEPLAY_TAG(Special, "Equipment.Slot.Special") // 특수 슬롯
        }
    }
}
