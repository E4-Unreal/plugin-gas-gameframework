#include "GGFShooterGameplayTags.h"

namespace GGFGameplayTags
{
    /* 상태 */
    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG(ADS, "State.ADS") // 조준
    }

    /* 입력 */
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG(Fire, "Input.Fire") // 총기 발사
        UE_DEFINE_GAMEPLAY_TAG(ADS, "Input.ADS") // 총기 조준
        UE_DEFINE_GAMEPLAY_TAG(Reload, "Input.Reload") // 총기 재장전
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
