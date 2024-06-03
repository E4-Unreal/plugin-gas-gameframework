#include "GGFShooterGameplayTags.h"

namespace GGFGameplayTags
{
    /* 게임플레이 큐 */
    namespace GameplayCue
    {
        namespace Hit
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue.Hit", "피격 이펙트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "GameplayCue.Hit.Test", "테스트 전용 피격 이펙트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "GameplayCue.Hit.Default", "기본 피격 이펙트")
        }

        namespace Explosion
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue.Explosion", "폭발 이펙트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "GameplayCue.Explosion.Test", "테스트 전용 폭발 이펙트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "GameplayCue.Explosion.Default", "기본 폭발 이펙트")
        }

        namespace Bounce
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue.Bounce", "바운스 이펙트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "GameplayCue.Bounce.Test", "테스트 전용 바운스 이펙트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "GameplayCue.Bounce.Default", "기본 바운스 이펙트")
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
