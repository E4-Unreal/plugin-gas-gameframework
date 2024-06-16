#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    /* 게임플레이 큐 */
    namespace GameplayCue
    {
        namespace FireArm
        {
            namespace Muzzle
            {
                GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default);
            }
        }
    }

    /* 상태 */
    namespace State
    {
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(ADS) // 조준 중인 상태
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Combat) // 전투 중인 상태
    }

    /* 행동 */
    namespace Action
    {
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Reload)
    }

    /* 입력 */
    namespace Input
    {
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fire) // 발사
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(ADS) // 조준
        GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Reload) // 재장전
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
                GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

                namespace AR
                {
                    GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
                    GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)
                }

                namespace SR
                {
                    GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
                    GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)
                }

                namespace SMG
                {
                    GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
                    GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)
                }

                namespace MG
                {
                    GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
                    GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)
                }

                namespace Pistol
                {
                    GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
                    GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)
                }

                namespace Launcher
                {
                    GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
                    GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)
                }

                namespace Shotgun
                {
                    GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
                    GGFSHOOTERCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)
                }
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

using namespace GGFGameplayTags;
