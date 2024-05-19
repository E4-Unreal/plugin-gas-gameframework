#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    /* 장비 */
    namespace Equipment
    {
        GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트

        /* 무기 */
        namespace Weapon
        {
            GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        }

        /* 방어구 */
        namespace Armor
        {
            GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        }

        /* 장신구 */
        namespace Accessory
        {
            GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        }

        /* 장비 슬롯 */
        namespace Slot
        {
            GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary) // 주 장비 슬롯
            GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Secondary) // 보조 장비 슬롯
            GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Special) // 특수 장비 슬롯
        }
    }
}
