#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    /* 상태 */
    namespace State
    {
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(ADS) // 조준
    }

    /* 입력 */
    namespace Input
    {
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fire) // 총기 발사
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(ADS) // 총기 조준
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Reload) // 총기 재장전
    }

    /* 장비 */
    namespace Equipment
    {
        /* 무기 */
        namespace Weapon
        {
            /* 화기 */
            namespace FireArm
            {
                GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
            }
        }
    }

    /* 부착물 */
    namespace Attachment
    {
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트

        namespace FireArm
        {
            GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트

            GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Muzzle) // 총구
            GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(IronSight) // 가늠쇠
            GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Scope) // 조준경
            GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Magazine) // 탄알집
            GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Grip) // 손잡이
            GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Laser) // 레이저
        }
    }
}
