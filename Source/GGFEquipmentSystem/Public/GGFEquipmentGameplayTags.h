#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    namespace Equipment
    {
        /* 루트 태그 */
        // 장비
        GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Equipment)

        // 무기
        namespace Weapon
        {
            GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon)

            // 화기
            namespace FireArm
            {
                GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FireArm)

                // 화기 부착물
                namespace Attachment
                {
                    GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment)

                    GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Muzzle) // 총구
                    GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(IronSight) // 가늠쇠
                    GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Scope) // 조준경
                    GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Magazine) // 탄알집
                    GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Grip) // 손잡이
                    GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Laser) // 레이저
                }
            }
        }

        // 방어구
        namespace Armor
        {
            GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Armor)
        }

        // 장신구
        namespace Accessory
        {
            GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Accessory)
        }

        // 장비 슬롯
        namespace Slot
        {
            GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Slot) // 루트
            GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary) // 주 장비 슬롯
            GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Secondary) // 보조 장비 슬롯
            GGFEQUIPMENTSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Special) // 특수 장비 슬롯
        }
    }
}
