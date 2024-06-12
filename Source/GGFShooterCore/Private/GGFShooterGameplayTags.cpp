#include "GGFShooterGameplayTags.h"

namespace GGFGameplayTags
{
    /* 게임플레이 큐 */
    namespace GameplayCue
    {
        namespace FireArm
        {
            namespace Muzzle
            {
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "GameplayCue.FireArm.Muzzle.Default", "기본 총구 이펙트")
            }
        }
    }

    /* 상태 */
    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(ADS, "State.ADS", "조준 중인 상태")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Combat, "State.Combat", "전투 중인 상태")
    }

    /* 입력 */
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fire, "Input.Fire", "발사 전용 입력 태그")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(ADS, "Input.ADS", "조준 전용 입력 태그")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Reload, "Input.Reload", "재장전 전용 입력 태그")
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
                UE_DEFINE_GAMEPLAY_TAG(Root, "Equipment.Weapon.FireArm") // 루트
            }
        }
    }

    /* 부착물 */
    namespace Attachment
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "Attachment") // 루트

        namespace FireArm
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Attachment.FireArm") // 루트

            UE_DEFINE_GAMEPLAY_TAG(Muzzle, "Attachment.FireArm.Muzzle") // 총구
            UE_DEFINE_GAMEPLAY_TAG(IronSight, "Attachment.FireArm.IronSight") // 가늠쇠
            UE_DEFINE_GAMEPLAY_TAG(Scope, "Attachment.FireArm.Scope") // 조준경
            UE_DEFINE_GAMEPLAY_TAG(Magazine, "Attachment.FireArm.Magazine") // 탄알집
            UE_DEFINE_GAMEPLAY_TAG(Grip, "Attachment.FireArm.Grip") // 손잡이
            UE_DEFINE_GAMEPLAY_TAG(Laser, "Attachment.FireArm.Laser") // 레이저
        }
    }
}
